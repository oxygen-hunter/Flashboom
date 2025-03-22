xmlDocPtr soap_xmlParseFile(const char *filename TSRMLS_DC)
{
	xmlParserCtxtPtr ctxt = NULL;
	xmlDocPtr ret;
	zend_bool old_allow_url_fopen;

/*
	xmlInitParser();
*/

	old_allow_url_fopen = PG(allow_url_fopen);
	PG(allow_url_fopen) = 1;
	ctxt = xmlCreateFileParserCtxt(filename);
        PG(allow_url_fopen) = old_allow_url_fopen;
        if (ctxt) {
                ctxt->keepBlanks = 0;
                ctxt->sax->ignorableWhitespace = soap_ignorableWhitespace;
                ctxt->sax->comment = soap_Comment;
                ctxt->sax->warning = NULL;
		/*ctxt->sax->fatalError = NULL;*/
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

	if (ret) {
		cleanup_xml_node((xmlNodePtr)ret);
	}
	return ret;
}


    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < size(nums1); ++i) {
            pairs.emplace_back(nums1[i], nums2[i]);
        }
        sort(begin(pairs), end(pairs));
        vector<tuple<int, int, int>> sorted_queries;
        for (int i = 0; i < size(queries); ++i) {
            sorted_queries.emplace_back(queries[i][0], queries[i][1], i);
        }
        sort(rbegin(sorted_queries), rend(sorted_queries));
        vector<int> result(size(queries));
        vector<pair<int, int>> stk;
        for (const auto& [x, y, i] : sorted_queries) {
            while (!empty(pairs) && pairs.back().first >= x) {
                const auto [a, b] = pairs.back(); pairs.pop_back();
                while (!empty(stk) && stk.back().second <= a + b) {
                    stk.pop_back();
                }
                if (empty(stk) || stk.back().first < b) {
                    stk.emplace_back(b, a + b);
                }
            }
            const auto it = lower_bound(cbegin(stk), cend(stk), pair(y, 0));
            result[i] = it != cend(stk) ? it->second : -1;
        }
        return result;
    }


