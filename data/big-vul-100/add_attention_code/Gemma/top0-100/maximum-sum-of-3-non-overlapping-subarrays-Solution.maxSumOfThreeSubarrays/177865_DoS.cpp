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


    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        const auto n = nums.size();
        vector<int> accu = {0};
        for (const auto& num : nums) {
            accu.emplace_back(accu.back() + num);
        }
       
        vector<int> left_pos(n);
        for (int i = k, total = accu[k] - accu[0]; i < n; ++i) {
            if (accu[i + 1] - accu[i + 1 - k] > total) {
                left_pos[i] = i + 1 - k;
                total = accu[i + 1] - accu[i + 1 - k];
            } else { 
                left_pos[i] = left_pos[i - 1];
            }
        }
        
        vector<int> right_pos(n, n - k);
        for (int i = n - k - 1, total = accu[n] - accu[n - k]; i >= 0; --i) {
            if (accu[i + k] - accu[i] > total) {
                right_pos[i] = i;
                total = accu[i + k] - accu[i];
            } else {
                right_pos[i] = right_pos[i + 1];
            }
        }
        
        vector<int> result(3);
        for (int i = k, max_sum = 0; i <= n - 2 * k; ++i) {
            auto left = left_pos[i - 1], right = right_pos[i + k];
            auto total = (accu[i + k] - accu[i]) +
                         (accu[left + k] - accu[left]) +
                         (accu[right + k] - accu[right]);
            if (total > max_sum) {
                max_sum = total;
                result = {left, i, right};
            }
        }
        return result;
    }


