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

    vector<int> movesToStamp(string stamp, string target) {
        const int M = stamp.size(), N = target.size();
        
        queue<int> q;
        vector<bool> lookup(N);
        vector<int> result;
        vector<pair<unordered_set<int>, unordered_set<int>>> A;
        for (int i = 0; i < N - M + 1; ++i) {
            unordered_set<int> made, todo;
            for (int j = 0; j < M; ++j) {
                if (stamp[j] == target[i + j]) {
                    made.emplace(i + j);
                } else {
                    todo.emplace(i + j);
                }
            }
            A.emplace_back(made, todo);
            if (!todo.empty()) {
                continue;
            }
            result.emplace_back(i);
            for (const auto& m : made) {
                if (lookup[m]) {
                    continue;
                }
                q.emplace(m);
                lookup[m] = true;
            }
        }
        
        while (!q.empty()) {
            auto i = q.front(); q.pop();
            for (int j = max(0, i - M + 1); j < min(N - M, i) + 1; ++j) {
                unordered_set<int>& made = A[j].first;
                unordered_set<int>& todo = A[j].second;
                if (!todo.count(i)) {
                    continue;
                }
                todo.erase(i);
                if (!todo.empty()) {
                    continue;
                }
                result.emplace_back(j);
                for (const auto& m : made) {
                    if (lookup[m]) {
                        continue;
                    }
                    q.emplace(m);
                    lookup[m] = true;
                }
            }
        }
        if (std::all_of(lookup.cbegin(), lookup.cend(), [](bool i){ return i; })) {
            reverse(result.begin(), result.end());
            return result;
        }
        return {};
    }

