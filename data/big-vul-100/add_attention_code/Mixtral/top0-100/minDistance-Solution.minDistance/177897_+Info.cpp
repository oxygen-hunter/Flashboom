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
               ctxt->options -= XML_PARSE_DTDLOAD;
                ctxt->sax->ignorableWhitespace = soap_ignorableWhitespace;
                ctxt->sax->comment = soap_Comment;
                ctxt->sax->warning = NULL;
		ctxt->sax->error = NULL;
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

        int minDistance(string word1, string word2) {
            const size_t m = word1.size();
            const size_t n = word2.size();

            if(m < n)
                return minDistance(word2, word1);

            vector<size_t> f(n + 1, 0);
            size_t upper_left;

            for(size_t i = 0; i < n + 1; ++i)
                f[i] = i;

            for(size_t i = 1; i < m + 1; ++i) {
                upper_left = f[0];
                f[0] = i;
                for(size_t j = 1; j < n + 1; ++j) {
                    size_t upper = f[j];
                    if(word1[i - 1] == word2[j - 1])
                        f[j] = upper_left;
                    else {
                        f[j] = 1 + min(upper_left, min(f[j - 1], f[j]));
                    }
                    upper_left = upper;
                }
            }

            return f[n];
        }

