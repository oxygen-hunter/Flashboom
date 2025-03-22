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


    vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
        static const unordered_map<char, pair<int, int>> directions = {
            {'U', {-1, 0}}, {'R', {0, 1}}, {'D', {1, 0}}, {'L', {0, -1}}
        };

        int x0 = startPos[0], y0 = startPos[1];
        int x = 0, y = 0;
        vector<int> result(size(s));
        iota(rbegin(result), rend(result), 1);
        unordered_map<int, vector<int>> lookup_x, lookup_y;
        lookup_x[x0 - x].emplace_back(0);
        lookup_y[y0 - y].emplace_back(0);
        for (int i = 0; i < size(s); ++i) {
            const auto& [dx, dy] = directions.at(s[i]);
            x += dx, y += dy;
            for (const auto& k : {n - x, -x - 1}) {
                if (!lookup_x.count(k)) {
                    continue;
                }
                for (const auto& j : lookup_x[k]) {
                    result[j] = min(result[j], i - j);
                }
                lookup_x.erase(k);
            }
            for (const auto& k : {n - y, -y - 1}) {
                if (!lookup_y.count(k)) {
                    continue;
                }
                for (const auto& j : lookup_y[k]) {
                    result[j] = min(result[j], i - j);
                }
                lookup_y.erase(k);
            }
            lookup_x[x0 - x].emplace_back(i + 1);
            lookup_y[y0 - y].emplace_back(i + 1);
        }
        return result;
    }


