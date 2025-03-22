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


    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        using P = pair<int, int>;
        vector<vector<P>> adj(N);
        for (const auto& edge: edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        unordered_map<int, int> best;
        best[0] = 0;
        unordered_map<int, unordered_map<int, int>> count;
        int result = 0;
        priority_queue<P, vector<P>, greater<P>> min_heap;
        min_heap.emplace(0, 0);
        while (!min_heap.empty()) {
            int curr_total, u;
            tie(curr_total, u) = min_heap.top(); min_heap.pop();
            if (best.count(u) && best[u] < curr_total) {
                continue;
            }
            ++result;
            for (const auto& kvp: adj[u]) {
                int v, w;
                tie(v, w) = kvp;
                count[u][v] = min(w, M - curr_total);
                int next_total = curr_total + w + 1;
                if (next_total <= M && 
                    (!best.count(v) || next_total < best[v])) {
                    best[v] = next_total;
                    min_heap.emplace(next_total, v);
                }
            }
        }
        for (const auto& edge: edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            result += min(w, count[u][v] + count[v][u]);
        }
        return result;
    }


