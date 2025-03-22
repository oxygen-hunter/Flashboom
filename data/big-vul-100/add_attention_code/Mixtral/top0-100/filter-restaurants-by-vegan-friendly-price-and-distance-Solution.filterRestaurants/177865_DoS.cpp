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

    vector<int> filterRestaurants(vector<vector<int>>& restaurants, int veganFriendly, int maxPrice, int maxDistance) {
        vector<int> result;
        unordered_map<int, int> lookup;
        for (int i = 0; i < restaurants.size(); ++i) {
            const auto& r = restaurants[i];
            if (r[2] >= veganFriendly && r[3] <= maxPrice && r[4] <= maxDistance) {
                lookup[r[0]] = i;  
                result.emplace_back(r[0]);
            }
        }
        sort(result.begin(), result.end(),
             [&restaurants, &lookup](const auto& i, const auto& j) {
                 return vector<int>{-restaurants[lookup[i]][1], -restaurants[lookup[i]][0]} <
                        vector<int>{-restaurants[lookup[j]][1], -restaurants[lookup[j]][0]};
             });
        return result;
    }

