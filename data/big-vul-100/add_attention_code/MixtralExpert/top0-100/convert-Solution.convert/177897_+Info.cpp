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


        string convert(string s, int nRows) {
            vector<string> row(nRows);
            string ans;
            int cnt = 0;

            if(nRows == 1)
                return s;

            for(auto c : s) {
                if(cnt < nRows) {
                    row[cnt].push_back(c);
                }
                else {
                    row[2 * nRows - 2 - cnt].push_back(c);
                }

                cnt = (cnt + 1) % (2 * nRows - 2);
            }

            for(auto s : row) {
                ans.append(s);
            }

            return ans;
        }


