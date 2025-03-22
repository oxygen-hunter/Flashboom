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


    int minimumDifference(vector<int>& nums) {
        vector<int> left, right; 
        for (int i = 0; i < size(nums); ++i) {
            if (i < size(nums) / 2) {
                left.emplace_back(nums[i]); 
            } else {
                right.emplace_back(nums[i]); 
            }
        }
        const auto& total1 = accumulate(cbegin(left), cend(left), 0);
        const auto& total2 = accumulate(cbegin(right), cend(right), 0);
        const int bound = (1 << size(left));
        unordered_map<int, vector<int>> sums;
        for (int mask = 0; mask < bound; ++mask) {
            int total = 0, bit = 1;
            for (const auto& x : left) {
                if (mask & bit) {
                    total += x; 
                }
                bit <<= 1;
            }
            sums[__builtin_popcount(mask)].emplace_back(2 * total - total1); 
        }
        for (auto& [_, v] : sums) {
            sort(begin(v), end(v));
        }
        int result = numeric_limits<int>::max();
        for (int mask = 0; mask < bound; ++mask) {
            int total = 0, bit = 1;
            for (const auto& x : right) {
                if (mask & bit) {
                    total += x; 
                }
                bit <<= 1;
            }
            const int k = size(right) - __builtin_popcount(mask);
            const int diff = 2 * total - total2; 
            const auto cit = lower_bound(cbegin(sums[k]), cend(sums[k]), -diff); 
            if (cit != cend(sums[k])) {
                result = min(result, abs(*cit + diff)); 
            }
            if (cit != cbegin(sums[k])) {
                result = min(result, abs(*prev(cit) + diff));    
            }
        }
        return result; 
    }


