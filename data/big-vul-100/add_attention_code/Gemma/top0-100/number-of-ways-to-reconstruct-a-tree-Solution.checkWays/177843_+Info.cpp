_PUBLIC_ size_t strlen_m_ext_handle(struct smb_iconv_handle *ic,
				    const char *s, charset_t src_charset, charset_t dst_charset)
{
	size_t count = 0;

#ifdef DEVELOPER
	switch (dst_charset) {
	case CH_DOS:
	case CH_UNIX:
		smb_panic("cannot call strlen_m_ext() with a variable dest charset (must be UTF16* or UTF8)");
	default:
		break;
	}

	switch (src_charset) {
	case CH_UTF16LE:
	case CH_UTF16BE:
		smb_panic("cannot call strlen_m_ext() with a UTF16 src charset (must be DOS, UNIX, DISPLAY or UTF8)");
	default:
		break;
	}
#endif
	if (!s) {
		return 0;
	}

	while (*s && !(((uint8_t)*s) & 0x80)) {
		s++;
		count++;
	}

	if (!*s) {
		return count;
	}
 
        while (*s) {
                size_t c_size;
               codepoint_t c = next_codepoint_handle_ext(ic, s, src_charset, &c_size);
                s += c_size;
 
                switch (dst_charset) {
		case CH_UTF16BE:
		case CH_UTF16MUNGED:
			if (c < 0x10000) {
				/* Unicode char fits into 16 bits. */
				count += 1;
			} else {
				/* Double-width unicode char - 32 bits. */
				count += 2;
			}
			break;
		case CH_UTF8:
			/*
			 * this only checks ranges, and does not
			 * check for invalid codepoints
			 */
			if (c < 0x80) {
				count += 1;
			} else if (c < 0x800) {
				count += 2;
			} else if (c < 0x10000) {
				count += 3;
			} else {
				count += 4;
			}
			break;
		default:
			/*
			 * non-unicode encoding:
			 * assume that each codepoint fits into
			 * one unit in the destination encoding.
			 */
			count += 1;
		}
	}

	return count;
}


    int checkWays(vector<vector<int>>& pairs) {
        unordered_map<int, unordered_set<int>> adj;
        for (const auto& pair : pairs) {
            adj[pair[0]].emplace(pair[1]);
            adj[pair[1]].emplace(pair[0]);
        }
        int n = size(adj);
        bool mul = false;
        unordered_set<int> lookup;
        vector<int> nodes;
        transform(begin(adj), end(adj), back_inserter(nodes),
                  [](const auto& kvp) { return kvp.first; });
        sort(begin(nodes), end(nodes),
             [&adj](const auto& a, const auto& b) {
                 return size(adj[a]) > size(adj[b]);
             });
        for (const auto& node : nodes) {
            lookup.emplace(node);
            int parent = 0;
            for (const auto& x : adj[node]) {
                if (!lookup.count(x)) {
                    continue;
                }
                if (parent == 0 || size(adj[x]) < size(adj[parent])) {
                    parent = x;
                }
            }
            if (parent) {
                for (const auto& x : adj[node]) {
                    if (x != parent && !adj[parent].count(x)) {
                        return 0;
                    }
                }
                mul |= size(adj[node]) == size(adj[parent]);
            } else if (size(adj[node]) != n - 1) {
                return 0;
            }
        }
        return 1 + mul;
    }


