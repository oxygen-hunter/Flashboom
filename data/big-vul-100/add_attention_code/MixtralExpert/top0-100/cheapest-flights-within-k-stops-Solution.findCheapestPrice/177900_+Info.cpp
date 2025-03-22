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


    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        using P = pair<int, int>;
        unordered_map<int, vector<P>> adj;
        for (const auto& flight : flights) {
            int u, v, w;
            tie(u, v, w) = make_tuple(flight[0], flight[1], flight[2]);
            adj[u].emplace_back(v, w);
        }
        
        unordered_map<int, unordered_map<int, int>> best;
        best[src][K + 1] = 0;
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(0, src, K + 1);
        while (!min_heap.empty()) {
            int result, u, k;
            tie(result, u, k) = min_heap.top(); min_heap.pop();
            if (k < 0 ||
                (best.count(u) && best[u].count(k) &&  best[u][k] < result)) {
                continue;
            }
            if (u == dst) {
                return result;
            }
            for (const auto& kvp : adj[u]) {
                int v, w;
                tie(v, w) = kvp;
                if (!best.count(v) ||
                    !best[v].count(k - 1) ||
                    result + w < best[v][k - 1]) {
                    best[v][k - 1] = result + w;
                    min_heap.emplace(result + w, v, k - 1);
                }
            }
        }
        return -1;
    }


