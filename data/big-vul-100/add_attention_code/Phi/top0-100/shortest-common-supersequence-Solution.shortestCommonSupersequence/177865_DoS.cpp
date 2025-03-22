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

    string shortestCommonSupersequence(string str1, string str2) {
        vector<vector<int>> dp(2, vector<int>(str2.size() + 1));
        vector<vector<tuple<int, int, char>>> bt(str1.size() + 1,
                                                 vector<tuple<int, int, char>>(str2.size() + 1));
        for (int i = 0; i < str1.length(); ++i) {
            bt[i + 1][0] = {i, 0, str1[i]};
        }
        for (int j = 0; j < str2.length(); ++j) {
            bt[0][j + 1] = {0, j, str2[j]};
        }
        for (int i = 0; i < str1.length(); ++i) {
            for (int j = 0; j < str2.length(); ++j) {
                if (dp[i % 2][j + 1] > dp[(i + 1) % 2][j]) {
                    dp[(i + 1) % 2][j + 1] = dp[i % 2][j + 1];
                    bt[i + 1][j + 1] = {i, j + 1, str1[i]};
                } else {
                    dp[(i + 1) % 2][j + 1] = dp[(i + 1) % 2][j];
                    bt[i + 1][j + 1] = {i + 1, j, str2[j]};
                }
                if (str1[i] != str2[j]) {
                    continue;
                }
                if (dp[i % 2][j] + 1 > dp[(i + 1) % 2][j + 1]) {
                    dp[(i + 1) % 2][j + 1] = dp[i % 2][j] + 1;
                    bt[i + 1][j + 1] = {i, j, str1[i]};
                }
            }
        }
        
        int i = str1.length(), j = str2.length();
        char c = 0;
        string result;
        while (i != 0 || j != 0) {
            tie(i, j, c) = bt[i][j];
            result.push_back(c);
        }
        reverse(result.begin(), result.end());
        return result;
    }

