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


    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        using P = pair<int, int>;
        unordered_map<int, vector<P>> adj;
        for (const auto& flight : flights) {
            int u, v, w;
            tie(u, v, w) = make_tuple(flight[0], flight[1], flight[2]);
            adj[u].emplace_back(v, w);
        }
        
        unordered_map<int, unordered_map<int, int>> best;
        best[src][K + 1] = 0;
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(0, src, K + 1);
        while (!min_heap.empty()) {
            int result, u, k;
            tie(result, u, k) = min_heap.top(); min_heap.pop();
            if (k < 0 ||
                (best.count(u) && best[u].count(k) &&  best[u][k] < result)) {
                continue;
            }
            if (u == dst) {
                return result;
            }
            for (const auto& kvp : adj[u]) {
                int v, w;
                tie(v, w) = kvp;
                if (!best.count(v) ||
                    !best[v].count(k - 1) ||
                    result + w < best[v][k - 1]) {
                    best[v][k - 1] = result + w;
                    min_heap.emplace(result + w, v, k - 1);
                }
            }
        }
        return -1;
    }


