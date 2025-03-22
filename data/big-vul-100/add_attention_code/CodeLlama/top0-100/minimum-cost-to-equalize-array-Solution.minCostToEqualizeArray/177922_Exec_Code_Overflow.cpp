 void add_param_to_argv(char *parsestart, int line)
 {
	int quote_open = 0, escaped = 0, param_len = 0;
	char param_buffer[1024], *curchar;
 
 	/* After fighting with strtok enough, here's now
 	 * a 'real' parser. According to Rusty I'm now no
			} else {
				param_buffer[param_len++] = *curchar;
 	for (curchar = parsestart; *curchar; curchar++) {
 		if (quote_open) {
 			if (escaped) {
				param_buffer[param_len++] = *curchar;
 				escaped = 0;
 				continue;
 			} else if (*curchar == '\\') {
		}

		switch (*curchar) {
 				quote_open = 0;
 				*curchar = '"';
 			} else {
				param_buffer[param_len++] = *curchar;
 				continue;
 			}
 		} else {
				continue;
			}
			break;
		default:
			/* regular character, copy to buffer */
			param_buffer[param_len++] = *curchar;

			if (param_len >= sizeof(param_buffer))
				xtables_error(PARAMETER_PROBLEM,
 		case ' ':
 		case '\t':
 		case '\n':
			if (!param_len) {
 				/* two spaces? */
 				continue;
 			}
 			break;
 		default:
 			/* regular character, copy to buffer */
			param_buffer[param_len++] = *curchar;
			if (param_len >= sizeof(param_buffer))
				xtables_error(PARAMETER_PROBLEM,
					      "Parameter too long!");
 			continue;
 		}
 
		param_buffer[param_len] = '\0';
 
 		/* check if table name specified */
		if ((param_buffer[0] == '-' &&
		     param_buffer[1] != '-' &&
		     strchr(param_buffer, 't')) ||
		    (!strncmp(param_buffer, "--t", 3) &&
		     !strncmp(param_buffer, "--table", strlen(param_buffer)))) {
 			xtables_error(PARAMETER_PROBLEM,
 				      "The -t option (seen in line %u) cannot be used in %s.\n",
 				      line, xt_params->program_name);
 		}
 
		add_argv(param_buffer, 0);
		param_len = 0;
 	}


    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        static const int MOD = 1e9 + 7;

        const int n = size(nums);
        const int64_t mx = ranges::max(nums);
        int64_t total = mx * n - accumulate(cbegin(nums), cend(nums), 0ll);
        // fill until mx with only cost1 operations
        if (n <= 2 || 2 * cost1 <= cost2) {
            return total * cost1 % MOD;
        }

        int64_t result = numeric_limits<int64_t>::max();
        // fill until mx with more cost2 operations and fewer cost1 operations
        const int64_t mn = ranges::min(nums);
        int64_t cnt1 = max((mx - mn) - (total - (mx - mn)), static_cast<int64_t>(0));
        int64_t cnt2 = total - cnt1;
        result = min(result, (cnt1 + cnt2 % 2) * cost1 + cnt2 / 2 * cost2);

        // fill until mx+x with most cost2 operations and fewest cost1 operations,
        // where x is the max of x s.t. cnt1+x >= (n-1)*x => cnt1 >= (n-2)*x
        const int64_t x = cnt1 / (n - 2);
        cnt1 %= n - 2;
        total += n * x;
        cnt2 = total - cnt1;
        result = min(result, (cnt1 + cnt2 % 2) * cost1 + (cnt2 / 2) * cost2);

        // fill until mx+x+1 or mx+x+2 with nearly all cost2 operations and at most one cost1 operation
        for (int _ = 0; _ < 2; ++_) {  // increase twice is for odd n
            total += n;
            result = min(result, total % 2 * cost1 + total / 2 * cost2);
        }
        return result % MOD;
    }


