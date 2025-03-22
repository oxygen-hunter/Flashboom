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

    int matrixMedian(vector<vector<int>>& grid) {
        const auto& check = [&](int x) {
            return accumulate(cbegin(grid), cend(grid), 0,
                              [&](const auto& total, const auto& curr) {
                                  return total + distance(cbegin(curr), upper_bound(cbegin(curr), cend(curr), x));
                              }) > size(grid) * size(grid[0]) / 2;
        };

        int left = min_element(cbegin(grid), cend(grid), [](const auto& a, const auto& b) { return a.front() < b.front(); })->front();
        int right = max_element(cbegin(grid), cend(grid), [](const auto& a, const auto& b) { return a.back() < b.back(); })->back();
        while (left <= right) {
            const int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

