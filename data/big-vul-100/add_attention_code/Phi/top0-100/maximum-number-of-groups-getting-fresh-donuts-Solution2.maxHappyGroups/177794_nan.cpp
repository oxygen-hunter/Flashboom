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

    int maxHappyGroups(int batchSize, vector<int>& groups) {
        vector<int> count(batchSize);
        for (const auto& i : groups) {
            ++count[i % size(count)];
        }
        int result = count[0];
        count[0] = 0;
        for (int i = 1; i <= size(count) / 2; ++i) {
            int pair_count = 2 * i != size(count) ? min(count[i], count[size(count) - i]) : count[i] / 2;
            result += pair_count;
            count[i] -= pair_count;
            count[size(count) - i] -= pair_count;
        }
        unordered_map<int, int> new_count;
        for (int i = 0; i < size(count); ++i) {
            if (count[i]) {
                new_count[i] = count[i];
            }
        }
        int max_mask = accumulate(cbegin(new_count), cend(new_count), 1,
                                  [](int total, pair<int, int> kvp) {
                                      return total * (kvp.second + 1);
                                  });
        vector<int> dp(max_mask);
        for (int mask = 0; mask < size(dp); ++mask) {
            int remain = 0;
            int curr = mask, basis = 1;
                for (const auto& [i, c] : new_count) {
                // mask: a0 + a1 * (c0 + 1)  + a2 * (c0 + 1) * (c1 + 1) + ... + a(b-1) * (c0 + 1) * (c1 + 1) * ... * (c(b-2) + 1)
                int ai = curr % (count[i] + 1);
                if (ai > 0) {
                    dp[mask] = max(dp[mask], dp[mask - basis]);
                }
                remain = (remain + ai * i) % batchSize;
                basis *= (c + 1), curr /= (c + 1);
            }
            if (mask != size(dp) - 1 && remain == 0) {
                ++dp[mask];
            }
        }
        return result + dp.back();
    }

