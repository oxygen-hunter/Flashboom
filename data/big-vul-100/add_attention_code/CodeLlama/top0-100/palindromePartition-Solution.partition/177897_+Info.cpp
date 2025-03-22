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


        vector<vector<string> > partition(string s) {
            const int n = s.size();
            bool p[n][n];

            fill_n(&p[0][0], n * n, false);

            for (int i = n - 1; i >= 0; --i)
                for (int j = i; j < n; ++j)
                    p[i][j] = s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1]);

            vector<vector<string> > sub_palins[n];
            for (int i = n - 1; i >= 0; --i) {
                for (int j = i; j < n; ++j)
                    if (p[i][j]) {
                        const string palindrome = s.substr(i, j - i + 1);
                        if (j + 1 < n) {
                            for (auto v : sub_palins[j + 1]) {
                                v.insert(v.begin(), palindrome);
                                sub_palins[i].push_back(v);
                            }
                        } 
                        else {
                            sub_palins[i].push_back(vector<string> { palindrome });
                        }
                    }
            }

            return sub_palins[0];
        }


