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


    vector<int> timeTaken(vector<int>& arrival, vector<int>& state) {
        enum {UNKNOWN = -1, ENTERING, EXITING};
        vector<int> result(size(arrival));
        int curr = numeric_limits<int>::min(), direction = UNKNOWN;
        vector<queue<int>> q(2);
        const auto& go_until = [&](int t) {
            while (curr <= t && any_of(cbegin(q), cend(q), [](const auto& x) { return !empty(x); })) {
                if (empty(q[direction])) {
                    direction ^= 1;
                }
                result[q[direction].front()] = curr++;
                q[direction].pop();
            }
        };

        for (int i = 0; i < size(arrival); ++i) {
            go_until(arrival[i] - 1);
            q[state[i]].emplace(i);
            if (!(arrival[i] <= curr)) {
                curr = arrival[i], direction = EXITING;
            }
        }
        go_until(numeric_limits<int>::max());
        return result;
    }


