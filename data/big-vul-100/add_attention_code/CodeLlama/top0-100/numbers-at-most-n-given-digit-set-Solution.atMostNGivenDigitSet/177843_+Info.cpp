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


    int atMostNGivenDigitSet(vector<string>& D, int N) {
        string str_N = to_string(N);
        unordered_set<string> set_D(D.cbegin(), D.cend());
        int result = 0;
        for (int i = 1 ; i < str_N.length() ; ++i) {
            result += pow(D.size(), i);  // x, xx, xxx
        }
        int i = 0;
        // assume N = 1234, D = 1, 2, 3, 4
        for (i = 0 ; i < str_N.length() ; ++i) {
            for (const auto& d : D) {
                if (d[0] < str_N[i]) {
                    // 11xx; 121x, 122x; 1231, 1232, 1233;
                    result += pow(D.size(), str_N.length() - i - 1);
                } else {
                    break;
                }
            }
            if (!set_D.count(string(1, str_N[i]))) {
                break;
            }
        }               
        return result + int(i == str_N.length());  // 1234
    }


