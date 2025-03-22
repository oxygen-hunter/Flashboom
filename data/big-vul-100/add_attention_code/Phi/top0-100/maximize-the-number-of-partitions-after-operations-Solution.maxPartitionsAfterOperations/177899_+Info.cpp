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

    int maxPartitionsAfterOperations(string s, int k) {
        vector<int> left(size(s) + 1);
        vector<int> left_mask(size(s) + 1);
        for (int i = 0, cnt = 0, mask = 0; i < size(s); ++i) {
            mask |= 1 << (s[i] - 'a');
            if (__builtin_popcount(mask) > k) {
                ++cnt;
                mask = 1 << (s[i] - 'a');
            }
            left[i + 1] = cnt;
            left_mask[i + 1] = mask;
        }
        vector<int> right(size(s) + 1);
        vector<int> right_mask(size(s) + 1);
        for (int i = size(s) - 1, cnt = 0, mask = 0; i >= 0; --i) {
            mask |= 1 << (s[i] - 'a');
            if (__builtin_popcount(mask) > k) {
                ++cnt;
                mask = 1 << (s[i] - 'a');
            }
            right[i] = cnt;
            right_mask[i] = mask;
        }

        int result = 0;
        for (int i = 0; i < size(s); ++i) {
            int curr = left[i] + right[i + 1];
            const int mask = left_mask[i] | right_mask[i + 1];
            if (__builtin_popcount(left_mask[i]) == k && __builtin_popcount(right_mask[i + 1]) == k && __builtin_popcount(mask) != 26) {
                curr += 3;
            } else if (__builtin_popcount(mask) + (__builtin_popcount(mask) != 26 ? 1 : 0) > k) {  // test case: s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", k = 26
                curr += 2;
            } else {
                curr += 1;
            }
            result = max(result, curr);
        }
        return result;
    }

