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

    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        const auto& check = [&](int i) {
            return nums[i - 1] < nums[i] && nums[i] > nums[i + 1];
        };

        BIT bit(size(nums));
        for (int i = 1; i + 1 < size(nums); ++i) {
            if (check(i)) {
                bit.add(i, +1);
            }
        }

        const auto& update = [&](int x, int d) {
            for (int i = max(x - 1, 1); i <= min(x + 1, static_cast<int>(size(nums)) - 2); ++i) {
                if (check(i)) {
                    bit.add(i, d);
                }
            }
        };

        vector<int> result;
        for (const auto& q : queries) {
            const int t = q[0], x = q[1], y = q[2];
            if (t == 1) {
                result.emplace_back(y - 1 >= x + 1 ? bit.query(y - 1) - bit.query((x + 1) - 1) : 0);
                continue;
            }
            update(x, -1);
            nums[x] = y;
            update(x, +1);
        }
        return result;
    }

