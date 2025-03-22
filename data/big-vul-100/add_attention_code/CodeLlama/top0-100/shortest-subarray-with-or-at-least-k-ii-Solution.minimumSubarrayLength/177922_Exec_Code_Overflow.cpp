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


    int minimumSubarrayLength(vector<int>& nums, int k) {
        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };
    
        const int total = accumulate(cbegin(nums), cend(nums), 0, [](const auto& x, const auto& y) {
            return x | y;
        });
        if (total < k) {
            return -1;
        }
        vector<int> cnt(bit_length(total));
        const auto& update = [&](int x, int d, int curr) {
            for (int i = 0; (1 << i) <= x; ++i) {
                if (!(x & (1 << i))) {
                    continue;
                }
                if (cnt[i] == 0) {
                    curr ^= 1 << i;
                }
                cnt[i] += d;
                if (cnt[i] == 0) {
                    curr ^= 1 << i;
                }
            }
            return curr;
        };

        int result = size(nums);
        for (int right = 0, left = 0, curr = 0; right < size(nums); ++right) {
            curr = update(nums[right], +1, curr);
            for (; left <= right && curr >= k; ++left) {
                result = min(result, right - left + 1);
                curr = update(nums[left], -1, curr);
            }
        }
        return result;
    }


