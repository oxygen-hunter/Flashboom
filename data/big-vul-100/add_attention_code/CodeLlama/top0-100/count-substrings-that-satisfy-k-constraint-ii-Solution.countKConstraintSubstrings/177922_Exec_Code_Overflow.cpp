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


    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        const auto& count = [](int64_t l) {
            return (l + 1) * l / 2;
        };

        vector<int64_t> prefix(size(s) + 1);
        vector<int> lookup(size(s), -1);
        for (int right = 0, left = 0, cnt = 0; right < size(s); ++right) {
            cnt += s[right] == '1' ? 1 : 0;
            while (!(cnt <= k || (right - left + 1) - cnt <= k)) {
                cnt -= s[left++] == '1' ? 1 : 0;
            }
            prefix[right + 1] = prefix[right] + (right - left + 1);
            lookup[left] = right;
        }
        assert(lookup[0] != -1);
        for (int i = 0; i + 1 < size(s); ++i) {
            if (lookup[i + 1] == -1) {
                lookup[i + 1] = lookup[i];
            }
        }
        vector<long long> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            const int left = queries[i][0], right = queries[i][1];
            const int new_right = min(lookup[left], right);
            result[i] = count(new_right - left + 1) + (prefix[right + 1] - prefix[new_right + 1]);
        }
        return result;
    }


