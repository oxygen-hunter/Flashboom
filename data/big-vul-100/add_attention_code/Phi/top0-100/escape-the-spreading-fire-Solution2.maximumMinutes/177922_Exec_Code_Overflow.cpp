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

    int maximumMinutes(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> directions{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        enum State {FIRE = 1, WALL, PERSON};
        const int INF = 1e9;
        const auto& bfs = [&]() {
            unordered_map<int, vector<vector<int>>> time;
            time[FIRE] = vector<vector<int>>(size(grid), vector<int>(size(grid[0]), INF));
            time[PERSON] = vector<vector<int>>(size(grid), vector<int>(size(grid[0]), INF));
            vector<tuple<int, int, int>> q;
            for (int r = 0; r < size(grid); ++r) {
                for (int c = 0; c < size(grid[0]); ++c) {
                    if (grid[r][c] == FIRE) {
                        q.emplace_back(r, c, FIRE);
                    }
                }
            }
            q.emplace_back(0, 0, PERSON);
            for (const auto& [r, c, t] : q) {
                time[t][r][c] = 0;
            }
            for (int d = 0; !empty(q); ++d) {
                vector<tuple<int, int, int>> new_q;
                for (const auto& [r, c, t] : q) {
                    for (const auto& [dr, dc] : directions) {
                        const int nr = r + dr, nc = c + dc;
                        if (!(0 <= nr && nr < size(grid) && 0 <= nc && nc < size(grid[0]) &&
                              grid[nr][nc] != WALL && time[t][nr][nc] == INF &&
                              (t == FIRE ||
                               d + 1 < time[FIRE][nr][nc] || (d + 1 == time[FIRE][nr][nc] && nr == size(grid) - 1 && nc == size(grid[0]) - 1)))) {
                            continue;
                        }
                        time[t][nr][nc] = d + 1;
                        new_q.emplace_back(nr, nc, t);
                    }
                }
                q = move(new_q);
            }
            return time;
        };
        auto time = bfs();
        if (time[PERSON][size(grid) - 1][size(grid[0]) - 1] == INF) {
            return -1;
        }
        if (time[FIRE][size(grid) - 1][size(grid[0]) - 1] == INF) {
            return INF;
        }
        const int diff = time[FIRE][size(grid) - 1][size(grid[0]) - 1] - time[PERSON][size(grid) - 1][size(grid[0]) - 1];
        return (time[FIRE][size(grid) - 1][size(grid[0]) - 2] - time[PERSON][size(grid) - 1][size(grid[0]) - 2] == diff + 2 ||
                time[FIRE][size(grid) - 2][size(grid[0]) - 1] - time[PERSON][size(grid) - 2][size(grid[0]) - 1] == diff + 2)
               ? diff
               : diff - 1;
    }

