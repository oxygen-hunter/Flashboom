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

    int maxProfit(int k, vector<int> &prices) {
        vector<int> profits;
        vector<pair<int, int>> v_p_stk;  // mono stack, where v is increasing and p is strictly decreasing
        for (int v = -1, p = -1; p + 1 < size(prices);) { // at most O(n) peaks, so v_p_stk and profits are both at most O(n) space
            for (v = p + 1; v + 1 < size(prices); ++v) {
                if (prices[v] < prices[v + 1]) {
                    break;
                }
            }
            for (p = v; p + 1 < size(prices); ++p) {
                if (prices[p] > prices[p + 1]) {
                    break;
                }
            }
            while (!empty(v_p_stk) && (prices[v_p_stk.back().first] > prices[v])) {  // not overlapped
                const auto [last_v, last_p] = move(v_p_stk.back()); v_p_stk.pop_back();
                profits.emplace_back(prices[last_p] - prices[last_v]);  // count [prices[last_v], prices[last_p]] interval
            }
            while (!empty(v_p_stk) && (prices[v_p_stk.back().second] <= prices[p])) {  // overlapped
                // prices[last_v] <= prices[v] <= prices[last_p] <= prices[p],
                // treat overlapped as [prices[v], prices[last_p]], [prices[last_v], prices[p]] intervals due to invariant max profit
                const auto [last_v, last_p] = move(v_p_stk.back()); v_p_stk.pop_back();
                profits.emplace_back(prices[last_p] - prices[v]);  // count [prices[v], prices[last_p]] interval
                v = last_v;  
            }
            v_p_stk.emplace_back(v, p);  // keep [prices[last_v], prices[p]] interval to check overlapped
        }        
        while (!empty(v_p_stk))  {
            const auto [last_v, last_p] = move(v_p_stk.back()); v_p_stk.pop_back();
            profits.emplace_back(prices[last_p] - prices[last_v]);  // count [prices[last_v], prices[last_p]] interval
        }
        if (k > size(profits)) {
            k = size(profits);
        } else {
            nth_element(begin(profits), begin(profits) + k - 1, end(profits), greater<int>());
        }
        return accumulate(cbegin(profits), cbegin(profits) + k, 0);  // top k profits of nonoverlapped intervals
    }

