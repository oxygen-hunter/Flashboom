xmlDocPtr soap_xmlParseMemory(const void *buf, size_t buf_size)
{
	xmlParserCtxtPtr ctxt = NULL;
	xmlDocPtr ret;

/*
	xmlInitParser();
*/
 */
        ctxt = xmlCreateMemoryParserCtxt(buf, buf_size);
        if (ctxt) {
                ctxt->sax->ignorableWhitespace = soap_ignorableWhitespace;
                ctxt->sax->comment = soap_Comment;
                ctxt->sax->warning = NULL;
#if LIBXML_VERSION >= 20703
		ctxt->options |= XML_PARSE_HUGE;
#endif
		xmlParseDocument(ctxt);
		if (ctxt->wellFormed) {
			ret = ctxt->myDoc;
			if (ret->URL == NULL && ctxt->directory != NULL) {
				ret->URL = xmlCharStrdup(ctxt->directory);
			}
		} else {
			ret = NULL;
			xmlFreeDoc(ctxt->myDoc);
			ctxt->myDoc = NULL;
		}
		xmlFreeParserCtxt(ctxt);
	} else {
		ret = NULL;
	}

/*
	xmlCleanupParser();
*/

/*
	if (ret) {
		cleanup_xml_node((xmlNodePtr)ret);
	}
*/
	return ret;
}

    int numDecodings(string s) {
        static const int M = 1000000007;
        static const int W = 3;
        vector<long long> dp(W);
        dp[0] = 1;
        dp[1] = s[0] == '*' ? 9 : (s[0] != '0' ? dp[0] : 0);
        for (int i = 1; i < s.length(); ++i) {
            if (s[i] == '*') {
                dp[(i + 1) % W] = 9 * dp[i % W];
                if (s[i - 1] == '1') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 9 * dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '2') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 6 * dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '*') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 15 * dp[(i - 1) % W]) % M;
                }
            } else {
                dp[(i + 1) % W] = s[i] != '0' ? dp[i % W] : 0;
                if (s[i - 1] == '1') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '2' && s[i] <= '6') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '*') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + (s[i] <= '6' ? 2 : 1) * dp[(i - 1) % W]) % M;
                }
            }
        }
        return static_cast<int>(dp[s.length() % W]);
    }

