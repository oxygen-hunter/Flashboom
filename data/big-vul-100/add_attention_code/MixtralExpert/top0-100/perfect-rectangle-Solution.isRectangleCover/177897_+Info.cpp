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


    bool isRectangleCover(vector<vector<int>>& rectangles) {
        enum Location {L = 0, B = 1, R = 2, T = 3};
        int left = numeric_limits<int>::max(), bottom = numeric_limits<int>::max(),
            right = numeric_limits<int>::min(), top = numeric_limits<int>::min();
        for (const auto& rect : rectangles) {
            left = min(left, rect[L]);
            bottom = min(bottom, rect[B]);
            right = max(right, rect[R]);
            top = max(top, rect[T]);
        }

        using P = pair<pair<int, int>, int>;
        enum Corner {LB = 1, RB = 2, LT = 4, RT = 8};
        unordered_map<int, unordered_map<int, int>> corner_count;
        vector<P> corners{{{L, B}, LB}, {{R, B}, RB}, {{L, T}, LT}, {{R, T}, RT}};
        for (const auto& rect : rectangles) {
            for (const auto& corner : corners) {
                const auto x = rect[corner.first.first];
                const auto y = rect[corner.first.second];
                if (corner_count[x][y] & corner.second) {
                    return false;
                }
                corner_count[x][y] |= corner.second;
            }
        }

        bitset<16> is_valid;
        is_valid[LB | RB] = is_valid[LB | LT] = is_valid[RB | RT] = is_valid[LT | RT] = is_valid[LB | RB | LT | RT] = true;
        for (auto itx = corner_count.cbegin(); itx != corner_count.cend(); ++itx) {
            const auto x = itx->first;
            for (auto ity = itx->second.cbegin(); ity != itx->second.cend(); ++ity) {
                const auto y = ity->first;
                const auto mask = ity->second;
                if ((left < x && x < right) || (bottom < y && y < top)) {
                    if (!is_valid[mask]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }


