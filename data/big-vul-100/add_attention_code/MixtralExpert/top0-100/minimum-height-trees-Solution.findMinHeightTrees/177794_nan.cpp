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


    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if (n == 1) {
            return {0};
        }

        unordered_map<int, unordered_set<int>> neighbors;
        for (const auto& e : edges) {
            int u, v;
            tie(u, v) = e;
            neighbors[u].emplace(v);
            neighbors[v].emplace(u);
        }

        vector<int> pre_level, cur_level;
        unordered_set<int> unvisited;
        for (int i = 0; i < n; ++i) {
            if (neighbors[i].size() == 1) {  // A leaf.
                pre_level.emplace_back(i);
            }
            unvisited.emplace(i);
        }

        // A graph can have 2 MHTs at most.
        // BFS from the leaves until the number 
        // of the unvisited nodes is less than 3.
        while (unvisited.size() > 2) {
            cur_level.clear();
            for (const auto& u : pre_level) {
                unvisited.erase(u);
                for (const auto& v : neighbors[u]) {
                    if (unvisited.count(v)) { 
                        neighbors[v].erase(u);
                        if (neighbors[v].size() == 1) {
                            cur_level.emplace_back(v);
                        }
                    }
                }
            }
            swap(pre_level, cur_level);
        }

        vector<int> res(unvisited.begin(), unvisited.end());
        return res;
    }


