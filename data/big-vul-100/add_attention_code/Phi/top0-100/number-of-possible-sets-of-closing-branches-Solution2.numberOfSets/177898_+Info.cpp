xmlDocPtr soap_xmlParseMemory(const void *buf, size_t buf_size)
{
	xmlParserCtxtPtr ctxt = NULL;
	xmlDocPtr ret;

/*
	xmlInitParser();
 */
        ctxt = xmlCreateMemoryParserCtxt(buf, buf_size);
        if (ctxt) {
               ctxt->options -= XML_PARSE_DTDLOAD;
                ctxt->sax->ignorableWhitespace = soap_ignorableWhitespace;
                ctxt->sax->comment = soap_Comment;
                ctxt->sax->warning = NULL;
		ctxt->sax->error = NULL;
		/*ctxt->sax->fatalError = NULL;*/
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

    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        static const int INF = numeric_limits<int>::max();
        const auto& check = [&](int mask, const auto& dist) {
            for (int i = 0; i < n; ++i) {
                if ((mask & (1 << i)) == 0) {
                    continue;
                }
                for (int j = i + 1; j < n; ++j) {
                    if ((mask & (1 << j)) == 0) {
                        continue;
                    }
                    if (dist[i][j] > maxDistance) {
                        return false;
                    }
                }
            }
            return true;
        };

        const auto& floydWarshall = [&](int mask, auto dist) {
            for (int k = 0; k < n; ++k) {
                if ((mask & (1 << k)) == 0) {
                    continue;
                }
                for (int i = 0; i < n; ++i) {
                    if ((mask & (1 << i)) == 0) {  // optional, to speed up performance
                        continue;
                    }
                    for (int j = i + 1; j < n; ++j) {
                        if ((mask & (1 << j)) == 0) {  // optional, to speed up performance
                            continue;
                        }
                        if (dist[i][k] != INF && dist[k][j] != INF) {
                            dist[j][i] = dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                        }
                    }
                }
            }
            return check(mask, dist);
        };

        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int u = 0; u < n; ++u) {
            dist[u][u] = 0;
        }
        for (const auto& r : roads) {
            dist[r[0]][r[1]] = min(dist[r[0]][r[1]], r[2]);
            dist[r[1]][r[0]] = min(dist[r[1]][r[0]], r[2]);
        }
        int result = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            result += floydWarshall(mask, dist);
        }
        return result;
    }

