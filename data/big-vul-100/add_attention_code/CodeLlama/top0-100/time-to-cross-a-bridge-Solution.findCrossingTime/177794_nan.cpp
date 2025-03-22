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


    int findCrossingTime(int n, int k, vector<vector<int>>& time) {
        vector<pair<int, int>> workers;
        for (int i = 0; i < k; ++i) {
            workers.emplace_back(time[i][0] + time[i][2], i);
        }
        priority_queue<pair<int, int>> left_bridge(cbegin(workers), cend(workers)), right_bridge;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> left_ware, right_ware;
        int curr = 0;
        while (n) {
            while (!empty(left_ware) && left_ware.top().first <= curr) {
                const auto [_, i] = left_ware.top(); left_ware.pop();
                left_bridge.emplace(time[i][0] + time[i][2], i);
            }
            while (!empty(right_ware) && right_ware.top().first <= curr) {
                const auto [_, i] = right_ware.top(); right_ware.pop();
                right_bridge.emplace(time[i][0] + time[i][2], i);
            }
            if (!empty(right_bridge)) {
                const auto [_, i] = right_bridge.top(); right_bridge.pop();
                curr += time[i][2];
                left_ware.emplace(curr + time[i][3], i);
                --n;
            } else if (!empty(left_bridge) && n - size(right_ware)) {
                const auto [_, i] = left_bridge.top(); left_bridge.pop();
                curr += time[i][0];
                right_ware.emplace(curr + time[i][1], i);
            } else {
                curr = min(!empty(left_ware) ? left_ware.top().first : numeric_limits<int>::max(),
                           !empty(right_ware) ? right_ware.top().first : numeric_limits<int>::max());
            }
        }
        return curr;
    }


