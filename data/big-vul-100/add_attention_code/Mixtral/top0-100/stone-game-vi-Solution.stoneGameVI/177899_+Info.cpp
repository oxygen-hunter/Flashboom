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

    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        vector<vector<int>> sorted_vals;
        vector<int> result(2);
        for (int i = 0; i < size(aliceValues); ++i) {
            sorted_vals.push_back({aliceValues[i] + bobValues[i],
                                   aliceValues[i], bobValues[i]});
        }
        sort(begin(sorted_vals), end(sorted_vals), greater<vector<int>>());
        for (int i = 0; i < size(sorted_vals); ++i) {
            result[i % 2] += sorted_vals[i][1 + i % 2];
        }
        return (result[0] == result[1]) ? 0 : (result[0] > result[1]) ? 1 : -1;
    }

