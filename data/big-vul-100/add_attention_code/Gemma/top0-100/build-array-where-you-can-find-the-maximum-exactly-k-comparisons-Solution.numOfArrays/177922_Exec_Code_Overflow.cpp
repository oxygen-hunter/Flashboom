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


    int numOfArrays(int n, int m, int k) {
        static const int MOD = 1e9 + 7;
        // dp[l][i][j] = number of ways of constructing array length l with max element i at search cost j
        vector<vector<vector<uint64_t>>> dp(2, vector<vector<uint64_t>>(m + 1, vector<uint64_t>(k + 1)));
        // prefix_dp[l][i][j] = sum(dp[l][i][j] for i in [1..i])
        vector<vector<vector<uint64_t>>> prefix_dp(2, vector<vector<uint64_t>>(m + 1, vector<uint64_t>(k + 1)));
        for (uint64_t i = 1; i <= m; ++i) {
            dp[1][i][1] = 1;
            prefix_dp[1][i][1] = (prefix_dp[1][i - 1][1] + dp[1][i][1]) % MOD;
        }
        for (uint64_t l = 2; l <= n; ++l) {
            for (uint64_t i = 1; i <= m; ++i) {
                for (uint64_t j = 1; j <= k; ++j) {
                    dp[l % 2][i][j] = (i * dp[(l - 1) % 2][i][j] % MOD + prefix_dp[(l - 1) % 2][i - 1][j - 1]) % MOD;
                    prefix_dp[l % 2][i][j] = (prefix_dp[l % 2][i - 1][j] + dp[l % 2][i][j]) % MOD;
                }
            }
        }
        return prefix_dp[n % 2][m][k];
    }


