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


    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        vector<tuple<int, bool, int>> events;
        for (int i = 0; i < size(times); ++i) {
            events.emplace_back(times[i][0], true, i);
            events.emplace_back(times[i][1], false, i);
        }
        sort(begin(events), end(events));

        unordered_map<int, int> lookup;
        priority_queue<int, vector<int>, greater<int>> min_heap;
        for (const auto& [_, arrival, i] : events) {
            if (!arrival) {
                min_heap.emplace(lookup[i]);
                lookup.erase(i);
                continue;
            }
            if (!empty(min_heap)) {
                lookup[i] = min_heap.top(); min_heap.pop();
            } else {
                lookup[i] = size(lookup);
            }
            if (i == targetFriend) {
                break;
            }
        }
        return lookup[targetFriend];
    }


