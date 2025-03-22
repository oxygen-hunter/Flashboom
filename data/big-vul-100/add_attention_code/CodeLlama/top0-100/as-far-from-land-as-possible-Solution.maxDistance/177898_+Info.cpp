xmlDocPtr soap_xmlParseMemory(const void *buf, size_t buf_size)
{
	xmlParserCtxtPtr ctxt = NULL;
	xmlDocPtr ret;

/*
	xmlInitParser();
 */
        ctxt = xmlCreateMemoryParserCtxt(buf, buf_size);
        if (ctxt) {
               ctxt->options -= XML_PARSE_DTDLOAD;
                ctxt->sax->ignorableWhitespace = soap_ignorableWhitespace;
                ctxt->sax->comment = soap_Comment;
                ctxt->sax->warning = NULL;
		ctxt->sax->error = NULL;
		/*ctxt->sax->fatalError = NULL;*/
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


    int maxDistance(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        queue<pair<int, int>> q;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j]) {
                    q.emplace(i, j);
                }
            }
        }
        if (q.size() == grid.size() * grid[0].size()) {
            return -1;
        }
        int level = -1;
        while (!q.empty()) {
            queue<pair<int, int>> next_q;
            while (!q.empty()) {
                const auto [x, y] = q.front(); q.pop();
                for (const auto& [dx, dy] : directions) {
                    const auto& nx = x + dx;
                    const auto& ny = y + dy;
                    if (!(0 <= nx && nx < grid.size() && 
                          0 <= ny && ny < grid[0].size() && 
                          grid[nx][ny] == 0)) {
                        continue;
                    }
                    next_q.emplace(nx, ny);
                    grid[nx][ny] = 1;
                }
            }
            q = move(next_q);
            ++level;
        }
        return level;
    }


