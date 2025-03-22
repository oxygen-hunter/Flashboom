 DynamicMetadataProvider::DynamicMetadataProvider(const DOMElement* e)
    : saml2md::DynamicMetadataProvider(e),
         m_verifyHost(XMLHelper::getAttrBool(e, true, verifyHost)),
         m_ignoreTransport(XMLHelper::getAttrBool(e, false, ignoreTransport)),
         m_encoded(true), m_trust(nullptr)
{
    const DOMElement* child = XMLHelper::getFirstChildElement(e, Subst);
    if (child && child->hasChildNodes()) {
        auto_ptr_char s(child->getFirstChild()->getNodeValue());
        if (s.get() && *s.get()) {
            m_subst = s.get();
            m_encoded = XMLHelper::getAttrBool(child, true, encoded);
            m_hashed = XMLHelper::getAttrString(child, nullptr, hashed);
        }
    }

    if (m_subst.empty()) {
        child = XMLHelper::getFirstChildElement(e, Regex);
        if (child && child->hasChildNodes() && child->hasAttributeNS(nullptr, match)) {
            m_match = XMLHelper::getAttrString(child, nullptr, match);
            auto_ptr_char repl(child->getFirstChild()->getNodeValue());
            if (repl.get() && *repl.get())
                m_regex = repl.get();
        }
    }

    if (!m_ignoreTransport) {
        child = XMLHelper::getFirstChildElement(e, _TrustEngine);
        string t = XMLHelper::getAttrString(child, nullptr, _type);
        if (!t.empty()) {
            TrustEngine* trust = XMLToolingConfig::getConfig().TrustEngineManager.newPlugin(t.c_str(), child);
            if (!dynamic_cast<X509TrustEngine*>(trust)) {
                delete trust;
                throw ConfigurationException("DynamicMetadataProvider requires an X509TrustEngine plugin.");
            }
            m_trust.reset(dynamic_cast<X509TrustEngine*>(trust));
            m_dummyCR.reset(XMLToolingConfig::getConfig().CredentialResolverManager.newPlugin(DUMMY_CREDENTIAL_RESOLVER, nullptr));
        }

        if (!m_trust.get() || !m_dummyCR.get())
            throw ConfigurationException("DynamicMetadataProvider requires an X509TrustEngine plugin unless ignoreTransport is true.");
    }
}


    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> count;
        for(int i = 0; i < size(nums); ++i) {
            ++count[nums[i]];
        }
        int total = (1 << size(quantity)) - 1;
        vector<int> requirement(total + 1);
        for (int mask = 0; mask < size(requirement); ++mask) {  // Time: O(2^m)
            for (int i = 0; i < size(quantity); ++i) {  // Time: O(m)
                if (mask & (1 << i)) {
                    requirement[mask] += quantity[i];
                }
            }
        }
        vector<vector<int>> dp(2, vector<int>(total + 1));
        dp[0][0] = 1;
        int i = 0;
        vector<int> cnts;
        for (const auto& [_, cnt] : count) {
            cnts.emplace_back(cnt);
        }
        if (size(quantity) < size(cnts)) {  // at most use top m cnts
            nth_element(begin(cnts), begin(cnts) + size(quantity) - 1, end(cnts), greater<int>());
            cnts.resize(size(quantity));
        }
        for (int i = 0; i < size(cnts); ++i) {  // Time: O(m)
            dp[(i + 1) % 2] = vector<int>(total + 1);
            // submask enumeration:
            // => sum(nCr(m, k) * 2^k for k in xrange(m+1)) = (1 + 2)^m = 3^m
            // => Time: O(3^m), see https://cp-algorithms.com/algebra/all-submasks.html
            for (int mask = total; mask >= 0; --mask) {
                dp[(i + 1) % 2][mask] |= dp[i % 2][mask];
                for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
                    if (requirement[submask] <= cnts[i] && dp[i % 2][mask ^ submask]) {
                        dp[(i + 1) % 2][mask] = 1;
                    }
                }
            }
        }
        return dp[size(cnts) % 2][total];
    }


