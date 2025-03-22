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


    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {
        const auto& addmod = [&](uint32_t a, uint32_t b, uint32_t mod) {  // avoid overflow
            a %= mod, b %= mod;
            if (mod - a <= b) {
                b -= mod;  // relied on unsigned integer overflow in order to give the expected results
            }
            return a + b;
        };

        const auto& mulmod = [&](uint32_t a, uint32_t b, uint32_t mod)  {  // avoid overflow
            a %= mod, b %= mod;
            uint32_t result = 0;
            if (a < b) {
                swap(a, b);
            }
            while (b > 0)  { 
                if (b % 2 == 1) {
                    result = addmod(result, a, mod);
                }
                a = addmod(a, a, mod);
                b /= 2; 
            } 
            return result; 
        };

        const auto& powmod = [&](uint32_t a, uint32_t b, uint32_t mod) {
            a %= mod;
            uint32_t result = 1;
            while (b) {
                if (b & 1) {
                    result = mulmod(result, a, mod);
                }
                a = mulmod(a, a, mod);
                b >>= 1;
            }
            return result;
        };

        vector<int> result;
        for (int i = 0; i < size(variables); ++i) {
            if (powmod(powmod(variables[i][0], variables[i][1], 10), variables[i][2], variables[i][3]) == target) {
                result.emplace_back(i);
            }
        }
        return result;
    }


