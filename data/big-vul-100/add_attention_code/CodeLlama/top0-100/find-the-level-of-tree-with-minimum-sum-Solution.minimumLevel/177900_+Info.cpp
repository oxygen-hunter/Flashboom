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


    int minimumLevel(TreeNode* root) {
        static const int64_t INF = numeric_limits<int64_t>::max();

        vector<TreeNode *> q = {root};
        pair<int64_t, int64_t> result = {INF, INF};
        for (int64_t d = 1; !empty(q); ++d) {
            vector<TreeNode *> new_q;
            int64_t total = 0ll;
            for (const auto& u : q) {
                if (u->left) {
                    new_q.emplace_back(u->left);
                }
                if (u->right) {
                    new_q.emplace_back(u->right);
                }
                total += u->val;
            }
            result = min(result, pair(total, d));
            q = move(new_q);
        }
        return result.second;
    }


