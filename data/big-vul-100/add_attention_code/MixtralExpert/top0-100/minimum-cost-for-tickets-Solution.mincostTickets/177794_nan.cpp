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


    int mincostTickets(vector<int>& days, vector<int>& costs) {
        static vector<int> durations{1, 7, 30};
        
        const int W = durations.back();
        vector<int> dp(W, numeric_limits<int>::max());
        dp[0] = 0;
        vector<int> last_buy_days{0, 0, 0};
        for (int i = 1; i < days.size() + 1; ++i) {
            dp[i % W] = numeric_limits<int>::max();
            for (int j = 0; j < durations.size(); ++j) {
                while (i - 1 < days.size() &&
                       days[i - 1] > days[last_buy_days[j]] + durations[j] - 1) {
                    ++last_buy_days[j];  // Time: O(n)
                }
                dp[i % W] = min(dp[i % W], dp[last_buy_days[j] % W] + costs[j]);
            }
        }
        return dp[days.size() % W];
    }


