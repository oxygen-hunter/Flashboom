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


    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        vector<pair<int, int>> idle;
        for (int i = 0; i < size(servers); ++i) {
            idle.emplace_back(servers[i], i);
        }
        make_heap(begin(idle), end(idle), greater<>());
        vector<tuple<int, int, int>> working;

        vector<int> result;
        for (int i = 0, t = 0; i < size(tasks); ++i) {
            t = !empty(idle) ? max(t, i) : get<0>(working.front());
            while (!empty(working) && get<0>(working.front()) <= t) {
                const auto [_, w, idx] = working.front(); pop_heap(begin(working), end(working), greater<>()); working.pop_back();
                idle.emplace_back(w, idx); push_heap(begin(idle), end(idle), greater<>());
            }
            const auto [w, idx] = idle.front(); pop_heap(begin(idle), end(idle), greater<>()); idle.pop_back();
            working.emplace_back(t + tasks[i], w, idx); push_heap(begin(working), end(working), greater<>());
            result.emplace_back(idx);
        }
        return result;
    }


