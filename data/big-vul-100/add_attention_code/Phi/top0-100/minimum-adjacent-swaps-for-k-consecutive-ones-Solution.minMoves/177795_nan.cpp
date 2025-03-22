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

    int minMoves(vector<int>& nums, int k) {
        vector<int> idxs;
        for (int i = 0; i < size(nums); ++i) {
            if (nums[i]) {
                idxs.emplace_back(i);
            }
        }
        vector<uint64_t> prefix(size(idxs) + 1);
        for (int i = 0; i < size(idxs); ++i) {
            prefix[i + 1] = prefix[i] + idxs[i];
        }
        const auto& score = [&prefix](int i, int j) {
                                return prefix[j + 1] - prefix[i];
                            };
        uint64_t result = numeric_limits<uint64_t>::max();
        for (int i = 0; i < size(idxs) - k + 1; ++i) {
            result = min(result, -score(i, i + k / 2 - 1) + score(i + (k + 1) / 2, i + k - 1));  // take each i+k//2 as median, find min dist to median
        }
        result -= (k / 2) * ((k + 1) / 2);  // rollback extra moves to the expected positions
        return result;
    }

