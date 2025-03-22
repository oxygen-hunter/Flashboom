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

    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        vector<int> prefix(size(s) / 2 + 1);
        vector<vector<int>> prefixs1(size(s) / 2 + 1, vector<int>(26));
        vector<vector<int>> prefixs2(size(s) / 2 + 1, vector<int>(26));
        for (int i = 0; i < size(s) / 2; ++i) {
            const int x = s[i] - 'a', y = s[(size(s) - 1) - i] - 'a';
            prefix[i + 1] = prefix[i] + (x != y ? 1 : 0);
            for (int j = 0; j < 26; ++j) {
                prefixs1[i + 1][j] = prefixs1[i][j] + (j == x ? 1 : 0);
                prefixs2[i + 1][j] = prefixs2[i][j] + (j == y ? 1 : 0);
            }
        }
    
        const auto& check = [&](int left1, int right1, int left2, int right2) {
            const auto& same = [&](int left, int right) {
                for (int i = 0; i < 26; ++i) {
                    if ((prefixs1[right + 1][i] - prefixs1[left][i]) - (prefixs2[right + 1][i] - prefixs1[left][i]) != 0) {
                        return false;
                    }
                }
                return true;
            };

            const auto& min_left = min(left1, left2), &max_left = max(left1, left2);
            const auto& min_right = min(right1, right2), &max_right = max(right1, right2);
            if (!(prefix[min_left] - prefix[0] == 0 && prefix.back() - prefix[max_right + 1] == 0)) {
                return false;
            }
            if (min_right < max_left) {  // non-overlapped
                return prefix[max_left] - prefix[min_right + 1] == 0 && same(min_left, min_right) && same(max_left, max_right);
            }
            // overlapped
            if ((left1 == min_left) == (right1 == max_right)) {  // inside another
                return same(min_left, max_right);
            }
            // not inside another
            auto p1 = &prefixs1, p2 = &prefixs2;
            if (min_left != left1) {
                swap(p1, p2);
            }
            for (int i = 0; i < 26; ++i) {
                const int d1 = ((*p1)[min_right + 1][i] - (*p1)[min_left][i]) - ((*p2)[max_left][i] - (*p2)[min_left][i]);
                const int d2 = ((*p2)[max_right + 1][i] - (*p2)[max_left][i]) - ((*p1)[max_right + 1][i] - (*p1)[min_right + 1][i]);
                if (!(d1 == d2 && d1 >= 0)) {  // test case: s = "aabbba", queries = [[0,1,3,4]]
                    return false;
                }
            }
            return true;
        };
    
        vector<bool> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = check(queries[i][0], queries[i][1], (size(s) - 1) - queries[i][3], (size(s) - 1) - queries[i][2]);
        }
        return result;
    }

