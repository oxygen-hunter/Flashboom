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


    void wallsAndGates(vector<vector<int>>& rooms) {
        const int INF = numeric_limits<int>::max();
        queue<pair<int, int>> q;
        for (int i = 0; i < rooms.size(); ++i) {
            for (int j = 0; j < rooms[0].size(); ++j) {
                if (rooms[i][j] == 0) {
                    q.emplace(i, j);
                }
            }
        }
        while (!q.empty()) {
            int i, j;
            tie(i, j) = q.front();
            q.pop();
            for (const pair<int, int>& d :
                 vector<pair<int, int>>{{i + 1, j}, {i - 1, j},
                                        {i, j + 1}, {i, j - 1}}) {
                int I, J;
                tie(I, J) = d;
                if (I >= 0 && I < rooms.size() &&
                    J >= 0 && J < rooms[0].size() &&
                    rooms[I][J] == INF) {
                    rooms[I][J] = rooms[i][j] + 1;
                    q.emplace(I, J);
                }
            }
        }
    }


