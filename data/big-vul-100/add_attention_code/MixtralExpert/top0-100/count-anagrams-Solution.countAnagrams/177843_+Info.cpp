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


    int countAnagrams(string s) {
        static const uint32_t MOD = 1e9 + 7;
        vector<int> fact = {1, 1};
        vector<int> inv = {1, 1};
        vector<int> inv_fact = {1, 1};
        const auto& lazy_init = [&](int n) {
            while (size(inv) <= n) {  // lazy initialization
                fact.emplace_back((static_cast<int64_t>(fact.back()) * size(inv)) % MOD);
                inv.emplace_back((static_cast<int64_t>(inv[MOD % size(inv)]) * (MOD - MOD / size(inv))) % MOD);  // https://cp-algorithms.com/algebra/module-inverse.html
                inv_fact.emplace_back((static_cast<int64_t>(inv_fact.back()) * inv.back()) % MOD);
            }
        };

        const auto& factorial = [&](int n) {
            lazy_init(n);
            return fact[n];
        };

        const auto& inv_factorial = [&](int n) {
            lazy_init(n);
            return inv_fact[n];
        };

        const auto& count = [&](int j, int i) {
            vector<int> cnt(26);
            for (int k = j; k <= i; ++k) {
                ++cnt[s[k] - 'a'];
            }
            int64_t result = 1;
            int total = 0;
            for (const auto& c : cnt) {
                total += c;
                result = (result * inv_factorial(c)) % MOD;
            }
            return (result * factorial(total)) % MOD;
        };

        int result = 1;
        for (int i = 0, j = 0; i < size(s); ++i) {
            if (i + 1 != size(s) && s[i + 1] != ' ') {
                continue;
            }
            result = (result * count(j, i)) % MOD;
            j = i + 2;
        }
        return result;
    }


