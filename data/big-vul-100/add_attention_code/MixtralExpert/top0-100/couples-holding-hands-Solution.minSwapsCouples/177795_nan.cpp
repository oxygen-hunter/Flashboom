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


    int minSwapsCouples(vector<int>& row) {
        int N = row.size() / 2;
        vector<vector<int>> couples(N);
        for (int seat = 0; seat < row.size(); ++seat) {
            couples[row[seat] / 2].emplace_back(seat / 2);
        }
        vector<vector<int>> adj(N);
        for (const auto& couple : couples) {
            adj[couple[0]].emplace_back(couple[1]);
            adj[couple[1]].emplace_back(couple[0]);
        }
        
        int result = 0;
        for (int couch = 0; couch < N; ++couch) {
            if (adj[couch].empty()) {
                continue;
            }
            int couch1 = couch;
            int couch2 = adj[couch1].back(); adj[couch1].pop_back();
            while (couch2 != couch) {
                ++result;
                adj[couch2].erase(find(adj[couch2].begin(), adj[couch2].end(), couch1));
                couch1 = couch2;
                couch2 = adj[couch1].back(); adj[couch1].pop_back();
            }
        }
        return result;  // also equals to N - (# of cycles)
    }


