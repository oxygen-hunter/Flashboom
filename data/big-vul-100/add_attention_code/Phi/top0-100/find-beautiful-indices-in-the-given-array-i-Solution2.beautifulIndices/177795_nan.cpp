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

    vector<int> beautifulIndices(string s, string a, string b, int k) {
        const auto& KMP = [&](const string& text, const string& pattern) {
            const auto& getPrefix = [&](const string& pattern) {
                vector<int> prefix(pattern.length(), -1);
                int j = -1;
                for (int i = 1; i < pattern.length(); ++i) {
                    while (j > -1 && pattern[j + 1] != pattern[i]) {
                        j = prefix[j];
                    }
                    if (pattern[j + 1] == pattern[i]) {
                        ++j;
                    }
                    prefix[i] = j;
                }
                return prefix;
            };

            vector<int> result;
            const vector<int> prefix = getPrefix(pattern + '#' + text);
            for (int i = (size(pattern) + 1) + (size(pattern) - 1); i < size(prefix); ++i) {
                if (prefix[i] + 1 == size(pattern)) {
                    result.emplace_back((i - (size(pattern) + 1)) - (size(pattern) - 1));
                }
            }
            return result;
        };

        vector<int> result;
        if (!(size(a) <= size(s) && size(b) <= size(s))) {
            return result;
        }
        const auto& lookup = KMP(s, b);
        int j = 0;
        for (const auto& i : KMP(s, a)) {
            const int j = distance(cbegin(lookup), lower_bound(cbegin(lookup), cend(lookup), i - k));
            if (j < size(lookup) && lookup[j] <= i + k) {
                result.emplace_back(i);
            }
        }
        return result;
    }

