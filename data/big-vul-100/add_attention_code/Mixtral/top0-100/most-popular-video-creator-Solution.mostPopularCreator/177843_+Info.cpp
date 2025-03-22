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

    vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) {
        unordered_map<string, int> cnt;
        unordered_map<string, pair<int, string>> lookup;
        for (int i = 0; i < size(creators); ++i) {
            cnt[creators[i]] += views[i];
            if (!lookup.count(creators[i])) {
                lookup[creators[i]] = {-views[i], ids[i]};
                continue;
            }
            lookup[creators[i]] = min(lookup[creators[i]], pair(-views[i], ids[i]));
        }
        int mx = 0;
        for (const auto& [_, v] : cnt) {
            mx = max(mx, v);
        }
        vector<vector<string>> result;
        for (const auto& [k, v] : cnt) {
            if (v != mx) {
                continue;
            }
            result.push_back({k, lookup[k].second});
        }
        return result;
    }

