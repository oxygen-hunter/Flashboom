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


    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        const auto n = nums.size();
        vector<int> accu = {0};
        for (const auto& num : nums) {
            accu.emplace_back(accu.back() + num);
        }
       
        vector<int> left_pos(n);
        for (int i = k, total = accu[k] - accu[0]; i < n; ++i) {
            if (accu[i + 1] - accu[i + 1 - k] > total) {
                left_pos[i] = i + 1 - k;
                total = accu[i + 1] - accu[i + 1 - k];
            } else { 
                left_pos[i] = left_pos[i - 1];
            }
        }
        
        vector<int> right_pos(n, n - k);
        for (int i = n - k - 1, total = accu[n] - accu[n - k]; i >= 0; --i) {
            if (accu[i + k] - accu[i] > total) {
                right_pos[i] = i;
                total = accu[i + k] - accu[i];
            } else {
                right_pos[i] = right_pos[i + 1];
            }
        }
        
        vector<int> result(3);
        for (int i = k, max_sum = 0; i <= n - 2 * k; ++i) {
            auto left = left_pos[i - 1], right = right_pos[i + k];
            auto total = (accu[i + k] - accu[i]) +
                         (accu[left + k] - accu[left]) +
                         (accu[right + k] - accu[right]);
            if (total > max_sum) {
                max_sum = total;
                result = {left, i, right};
            }
        }
        return result;
    }


