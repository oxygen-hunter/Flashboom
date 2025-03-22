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


    string reformatNumber(string number) {
        int src_len = 0;
        for (const auto& c : number) {  // remove non-digit characters
            if (isdigit(c)) {
                number[src_len++] = c;
            }
        }
        int dst_len = src_len + (src_len - 1) / 3;
        number.resize(dst_len);  // resize the buffer to expected final size
        for (int i = src_len - 1, curr = dst_len - 1, l = (3 - src_len % 3) % 3; i >= 0; --i, ++l) {
            if (l && l % 3 == 0) {  // group by 3 digits
                number[curr--] = '-';
            }
            number[curr--] = number[i];
        }
        if (dst_len >= 3 && number[dst_len - 2] == '-') {  // adjust for the 4 digits case
            swap(number[dst_len - 3], number[dst_len - 2]);
        }
        return number;
    }


