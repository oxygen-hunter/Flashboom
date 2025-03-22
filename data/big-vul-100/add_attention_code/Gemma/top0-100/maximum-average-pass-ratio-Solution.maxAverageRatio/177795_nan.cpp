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


    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        static const auto& profit = [](double a, double b) {
            return (a + 1) / (b + 1) - a / b;
        };

        vector<tuple<double, int, int>> max_heap;
        for (const auto& c : classes) {
            max_heap.emplace_back(profit(c[0], c[1]), c[0], c[1]);
        }
        make_heap(begin(max_heap), end(max_heap));
        for (; extraStudents > 0; --extraStudents) {
            auto [_, a, b] = max_heap.front();
            ++a, ++b;
            pop_heap(begin(max_heap), end(max_heap)); max_heap.pop_back();
            max_heap.emplace_back(profit(a, b), a, b); push_heap(begin(max_heap), end(max_heap));
        }
        return accumulate(cbegin(max_heap), cend(max_heap), 0.0,
                          [](const auto& total, const auto& x) {
                              return total + float(get<1>(x)) / get<2>(x);
                          }) / size(classes);
    }


