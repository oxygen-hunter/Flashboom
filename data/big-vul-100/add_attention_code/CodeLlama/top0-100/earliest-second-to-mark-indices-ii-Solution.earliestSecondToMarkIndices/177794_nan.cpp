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


    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        vector<int> lookup(size(nums), -1);
        for (int i = size(changeIndices) - 1; i >= 0; --i) {
            if (nums[changeIndices[i] - 1]) {
                lookup[changeIndices[i] - 1] = i;
            }
        }
        const int64_t total = accumulate(cbegin(nums), cend(nums), 0ll) + size(nums);
        const auto& check = [&](int t) {
            priority_queue<int, vector<int>, greater<int>> min_heap;
            int64_t total2 = 0, cnt = 0;
            for (int i = t - 1; i >= 0; --i) {
                if (i != lookup[changeIndices[i] - 1]) {
                    ++cnt;
                    continue;
                }
                min_heap.emplace(nums[changeIndices[i] - 1]);
                total2 += nums[changeIndices[i] - 1];
                if (cnt) {
                    --cnt;
                } else {
                    ++cnt;
                    total2 -= min_heap.top(); min_heap.pop();
                }
            }
            return total - (total2 + (size(min_heap))) <= cnt;
        };
    
        int64_t total2 = 0;
        for (int i = 0; i < size(nums); ++i) {
            total2 += lookup[i] != -1 ? 1 : nums[i];
        }
        int64_t left = total2 + size(nums), right = size(changeIndices);
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left <= size(changeIndices) ? left : -1;
    }


