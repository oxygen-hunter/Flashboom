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


    int numDecodings(string s) {
        static const int M = 1000000007;
        static const int W = 3;
        vector<long long> dp(W);
        dp[0] = 1;
        dp[1] = s[0] == '*' ? 9 : (s[0] != '0' ? dp[0] : 0);
        for (int i = 1; i < s.length(); ++i) {
            if (s[i] == '*') {
                dp[(i + 1) % W] = 9 * dp[i % W];
                if (s[i - 1] == '1') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 9 * dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '2') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 6 * dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '*') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + 15 * dp[(i - 1) % W]) % M;
                }
            } else {
                dp[(i + 1) % W] = s[i] != '0' ? dp[i % W] : 0;
                if (s[i - 1] == '1') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '2' && s[i] <= '6') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + dp[(i - 1) % W]) % M;
                } else if (s[i - 1] == '*') {
                    dp[(i + 1) % W] = (dp[(i + 1) % W] + (s[i] <= '6' ? 2 : 1) * dp[(i - 1) % W]) % M;
                }
            }
        }
        return static_cast<int>(dp[s.length() % W]);
    }


