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

    int dieSimulator(int n, vector<int>& rollMax) {
        static const int MOD = 1e9 + 7;
        vector<vector<int>> dp;
        for (int i = 0; i < 6; ++i) {
            dp.emplace_back(rollMax[i]);
            dp[i][0] = 1;  // 0-indexed
        }
        while (--n) {
            vector<vector<int>> new_dp;
            for (int i = 0; i < 6; ++i) {
                new_dp.emplace_back(rollMax[i]);  
            }
            for (int i = 0; i < 6; ++i) {
                for (int k = 0; k < rollMax[i]; ++k) {
                    for (int j = 0; j < 6; ++j) {
                        if (i == j) {
                            if (k < rollMax[i] - 1) {  // 0-indexed
                                new_dp[j][k + 1] = (new_dp[j][k + 1] + dp[i][k]) % MOD;
                            }
                        } else {
                            new_dp[j][0] = (new_dp[j][0] + dp[i][k]) % MOD;
                        }
                    }
                }
            }
            dp = move(new_dp);
        }
        uint64_t result = 0;
        for (const auto& row : dp) {
            const auto& total =
                accumulate(row.cbegin(), row.cend(),
                           0ull,
                           [&](const auto& a, const auto& b) {
                               return (a + b) % MOD;
                           });
            result = (result + total) % MOD;
        }
        return result;
    }

