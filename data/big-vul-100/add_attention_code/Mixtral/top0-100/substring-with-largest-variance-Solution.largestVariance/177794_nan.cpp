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

    int largestVariance(string s) {
        const auto& modified_kadane = [&s](const auto& x, const auto& y) {
            int result = 0;
            vector<int> lookup(2);
            vector<int> remain = {static_cast<int>(count(cbegin(s), cend(s), x)),
                                  static_cast<int>(count(cbegin(s), cend(s), y))};
            int curr = 0;
            for (const auto& c : s) {
                if (!(c == x || c == y)) {
                    continue;
                }
                lookup[c != x] = 1;
                --remain[c != x];
                curr += (c == x) ? 1 : -1;
                if (curr < 0 && remain[0] && remain[1]) {
                    curr = lookup[0] = lookup[1] = 0;  // reset states if the remain has both x, y
                }
                if (lookup[0] && lookup[1]) {
                    result = max(result, curr);  // update result if x, y both exist
                }
            }
            return result;
        };
        
        unordered_set<char> alphabets(cbegin(s), cend(s));
        int result = 0;
        for (const auto& x : alphabets) {
            for (const auto& y: alphabets) {
                if (x != y) {
                    result = max(result, modified_kadane(x, y));
                }
            }
        }
        return result;
    }

