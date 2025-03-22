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


    vector<int> recoverArray(vector<int>& nums) {    
        auto check = [&nums](int k, unordered_map<int, int> cnt, vector<int> *result) {
            for (const auto& x : nums) {
                if (cnt[x] == 0) {
                    continue;
                }
                if (cnt[x + 2 * k] == 0) {
                    return false;
                }
                --cnt[x];
                --cnt[x + 2 * k];
                result->emplace_back(x + k);
            }
            return true;
        };
        sort(begin(nums), end(nums));
        unordered_map<int, int> cnt;
        for (const auto& x : nums) {
            ++cnt[x];
        }
        for (int i = 1; i <= size(nums) / 2; ++i) {
            int k = nums[i] - nums[0];
            if (k == 0 || k % 2) {
                continue;
            }
            k /= 2;
            vector<int> result;
            if (check(k, cnt, &result)) {
                return result;
            }
        }
        return {};
    }


