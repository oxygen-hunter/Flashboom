PatternMatch(char *pat, int patdashes, char *string, int stringdashes)
{
    char        c,
                t;

    if (stringdashes < patdashes)
	return 0;
    for (;;) {
	switch (c = *pat++) {
	case '*':
	    if (!(c = *pat++))
		return 1;
	    if (c == XK_minus) {
		patdashes--;
		for (;;) {
		    while ((t = *string++) != XK_minus)
			if (!t)
			    return 0;
		    stringdashes--;
		    if (PatternMatch(pat, patdashes, string, stringdashes))
			return 1;
		    if (stringdashes == patdashes)
			return 0;
		}
	    } else {
		for (;;) {
		    while ((t = *string++) != c) {
			if (!t)
			    return 0;
			if (t == XK_minus) {
			    if (stringdashes-- < patdashes)
				return 0;
			}
		    }
		    if (PatternMatch(pat, patdashes, string, stringdashes))
			return 1;
 		}
 	    }
 	case '?':
	    if (*string++ == XK_minus)
 		stringdashes--;
 	    break;
 	case '\0':
 	    return (*string == '\0');
		patdashes--;
		stringdashes--;
		break;
	    }
	    return 0;
	default:
	    if (c == *string++)
		break;
	    return 0;
	}
    }

    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {
        const auto& addmod = [&](uint32_t a, uint32_t b, uint32_t mod) {  // avoid overflow
            a %= mod, b %= mod;
            if (mod - a <= b) {
                b -= mod;  // relied on unsigned integer overflow in order to give the expected results
            }
            return a + b;
        };

        const auto& mulmod = [&](uint32_t a, uint32_t b, uint32_t mod)  {  // avoid overflow
            a %= mod, b %= mod;
            uint32_t result = 0;
            if (a < b) {
                swap(a, b);
            }
            while (b > 0)  { 
                if (b % 2 == 1) {
                    result = addmod(result, a, mod);
                }
                a = addmod(a, a, mod);
                b /= 2; 
            } 
            return result; 
        };

        const auto& powmod = [&](uint32_t a, uint32_t b, uint32_t mod) {
            a %= mod;
            uint32_t result = 1;
            while (b) {
                if (b & 1) {
                    result = mulmod(result, a, mod);
                }
                a = mulmod(a, a, mod);
                b >>= 1;
            }
            return result;
        };

        vector<int> result;
        for (int i = 0; i < size(variables); ++i) {
            if (powmod(powmod(variables[i][0], variables[i][1], 10), variables[i][2], variables[i][3]) == target) {
                result.emplace_back(i);
            }
        }
        return result;
    }

