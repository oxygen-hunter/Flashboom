 DynamicMetadataProvider::DynamicMetadataProvider(const DOMElement* e)
    : AbstractMetadataProvider(e),
       m_validate(XMLHelper::getAttrBool(e, false, validate)),
         m_id(XMLHelper::getAttrString(e, "Dynamic", id)),
         m_lock(RWLock::create()),
        m_refreshDelayFactor(0.75),
        m_minCacheDuration(XMLHelper::getAttrInt(e, 600, minCacheDuration)),
        m_maxCacheDuration(XMLHelper::getAttrInt(e, 28800, maxCacheDuration)),
        m_shutdown(false),
        m_cleanupInterval(XMLHelper::getAttrInt(e, 1800, cleanupInterval)),
        m_cleanupTimeout(XMLHelper::getAttrInt(e, 1800, cleanupTimeout)),
         m_cleanup_wait(nullptr), m_cleanup_thread(nullptr)
 {
     if (m_minCacheDuration > m_maxCacheDuration) {
        Category::getInstance(SAML_LOGCAT ".MetadataProvider.Dynamic").error(
             "minCacheDuration setting exceeds maxCacheDuration setting, lowering to match it"
             );
         m_minCacheDuration = m_maxCacheDuration;
    }

    const XMLCh* delay = e ? e->getAttributeNS(nullptr, refreshDelayFactor) : nullptr;
    if (delay && *delay) {
        auto_ptr_char temp(delay);
        m_refreshDelayFactor = atof(temp.get());
        if (m_refreshDelayFactor <= 0.0 || m_refreshDelayFactor >= 1.0) {
            Category::getInstance(SAML_LOGCAT ".MetadataProvider.Dynamic").error(
                "invalid refreshDelayFactor setting, using default"
                );
            m_refreshDelayFactor = 0.75;
        }
    }

    if (m_cleanupInterval > 0) {
        if (m_cleanupTimeout < 0)
            m_cleanupTimeout = 0;
        m_cleanup_wait = CondWait::create();
        m_cleanup_thread = Thread::create(&cleanup_fn, this);
    }
}

    long long getMaxFunctionValue(vector<int>& receiver, long long k) {
        const auto& find_cycles = [](const auto& adj) {
            vector<pair<int, int>> result;
            vector<int> lookup(size(adj));
            for (int i = 0, idx = 0; i < size(adj); ++i) {
                int u = i, prev = idx;
                while (!lookup[u]) {
                    lookup[u] = ++idx;
                    u = adj[u];
                }
                if (lookup[u] > prev) {
                    result.emplace_back(u, idx - lookup[u] + 1);
                }
            }
            return result;
        };
        
        const auto& cycles = find_cycles(receiver);
        vector<pair<int, int>> lookup(size(receiver), {-1, -1});
        vector<vector<int64_t>> prefixes(size(cycles), vector<int64_t>(1));
        const auto& find_prefixes = [&](const auto& cycles) {
            for (int idx = 0; idx < size(cycles); ++idx) {
                auto [u, l] = cycles[idx];
                for (int i = 0; i < l; ++i) {
                    lookup[u] = {idx, i};
                    prefixes[idx].emplace_back(prefixes[idx][i] + u);
                    u = receiver[u];
                }
            }
        };
        
        const auto& get_sum = [](const auto& prefix, int64_t i, int64_t cnt) {
            const int64_t l = size(prefix) - 1;
            const int64_t q = cnt / l;
            const int64_t r = cnt % l;
            return (q * prefix.back() +
                    (prefix[min(i + r, l)] - prefix[i]) +
                    (prefix[max((i + r) - l, static_cast<int64_t>(0))] - prefix[0]));
        };
        
        const auto& start_inside_cycle = [&]() {
            int64_t result = 0;
            for (auto [u, l] : cycles) {
                for (int _ = 0; _ < l; ++_) {
                    const auto& [idx, i] = lookup[u];
                    result = max(result, get_sum(prefixes[idx], i, k + 1));
                    u = receiver[u];
                }
            }
            return result;
        };
    
        const auto& start_outside_cycle = [&]() {
            int64_t result = 0;
            vector<int> degree(size(receiver));
            for (const auto& x : receiver) {
                ++degree[x];
            }
            for (int u = 0; u < size(receiver); ++u) {
                if (degree[u]) {
                    continue;
                }
                int64_t curr = 0;
                deque<int> dq;
                int v = u;
                while (lookup[v].first == -1) {
                    curr += v;
                    dq.emplace_back(v);
                    if (size(dq) == k + 1) {
                        result = max(result, curr);
                        curr -= dq.front(); dq.pop_front();
                    }
                    v = receiver[v];
                }
                const auto& [idx, i] = lookup[v];
                while (!empty(dq)) {
                    result = max(result, curr + get_sum(prefixes[idx], i, (k + 1) - size(dq)));
                    curr -= dq.front(); dq.pop_front();
                }
            }
            return result;
        };
              
        find_prefixes(cycles);
        return max(start_inside_cycle(), start_outside_cycle());
    }

