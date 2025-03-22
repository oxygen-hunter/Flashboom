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


    int shortestPathWithHops(int n, vector<vector<int>>& edges, int s, int d, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
            adj[e[1]].emplace_back(e[0], e[2]);
        }
        const auto& modified_dijkstra = [&]() {
            static const int INF = numeric_limits<int>::max();

            vector<vector<int>> best(size(adj), vector<int>(k + 1, INF));
            best[s][0] = 0;
            priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> min_heap;
            min_heap.emplace(best[s][0], s, 0);
            while (!empty(min_heap)) {
                const auto [curr, u, cnt] = min_heap.top(); min_heap.pop();
                if (curr > best[u][cnt]) {
                    continue;
                }
                if (u == d) {
                    return curr;
                }
                for (const auto& [v, w] : adj[u]) {
                    if (w < best[v][cnt] - curr) {
                        best[v][cnt] = curr + w;
                        min_heap.emplace(best[v][cnt], v, cnt);
                    }
                    if (cnt + 1 <= k && curr < best[v][cnt + 1]) {
                        best[v][cnt + 1] = curr;
                        min_heap.emplace(best[v][cnt + 1], v, cnt + 1);
                    }
                }
            }
            return -1;
        };

        return modified_dijkstra();
    }


