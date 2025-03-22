parse_object(JsonLexContext *lex, JsonSemAction *sem)
{
	/*
	 * an object is a possibly empty sequence of object fields, separated by
	 * commas and surrounded by curly braces.
	 */
	json_struct_action ostart = sem->object_start;
    json_struct_action oend = sem->object_end;
    JsonTokenType tok;
 
    if (ostart != NULL)
        (*ostart) (sem->semstate);
 
	 * itself. Note that we increment this after we call the semantic routine
	 * for the object start and restore it before we call the routine for the
	 * object end.
	 */
	lex->lex_level++;

	/* we know this will succeeed, just clearing the token */
	lex_expect(JSON_PARSE_OBJECT_START, lex, JSON_TOKEN_OBJECT_START);

	tok = lex_peek(lex);
	switch (tok)
	{
		case JSON_TOKEN_STRING:
			parse_object_field(lex, sem);
			while (lex_accept(lex, JSON_TOKEN_COMMA, NULL))
				parse_object_field(lex, sem);
			break;
		case JSON_TOKEN_OBJECT_END:
			break;
		default:
			/* case of an invalid initial token inside the object */
			report_parse_error(JSON_PARSE_OBJECT_START, lex);
	}

	lex_expect(JSON_PARSE_OBJECT_NEXT, lex, JSON_TOKEN_OBJECT_END);

	lex->lex_level--;

	if (oend != NULL)
		(*oend) (sem->semstate);
}


    string largestPalindrome(int n, int k) {
        const auto& powmod = [](uint32_t a, uint32_t b, uint32_t mod) {
            a %= mod;
            uint64_t result = 1;
            while (b) {
                if (b & 1) {
                    result = result * a % mod;
                }
                a = uint64_t(a) * a % mod;
                b >>= 1;
            }
            return result;
        };

        const auto& inv = [&](int x, int p) {
            return powmod(x, p - 2, p);
        };

        const auto& f = [&](int l) {
            static const int p = 7;
            string result(l, '9');
            if (l == 0) {
                return result;
            }
            int curr = 0;
            for (const auto& x : result) {
                curr = (curr * 10 + (x - '0')) % p;
            }
            // l%2 == 0: (curr+(i-9)*11*pow(10, l//2-1, p))%p = 0
            // l%2 == 1: (curr+(i-9)*pow(10, l//2, p))%p = 0
            int i = 9 - (curr * inv(l % 2 == 0 ? 11 : 1, p) * inv(powmod(10, l / 2 - (l % 2 == 0 ? 1 : 0), p), p)) % p;
            if (i <= 2) {
                i += p;
            }
            result[l / 2] = result[l / 2 - (l % 2 == 0 ? 1 : 0)] = '0' + i;
            return result;
        };

        if (k == 1 || k == 3 || k == 9) {
            return string(n, '9');
        }
        if (k == 2 || k == 4 || k == 8) {
            k = min(k, 6);
            if (n <= k) {
                return string(n, '8');
            }
            const int l = k / 2;
            return string(l, '8') + string(n - k, '9') + string(l, '8');
        }
        if (k == 5) {
            if (n <= 2) {
                return string(n, '5');
            }
            return string(1, '5') + string(n - 2, '9') + string(1, '5');
        }
        if (k == 6) {
            if (n <= 2) {
                return string(n, '6');
            }
            if (n % 2) {
                const int l = n / 2 - 1;
                return string(1, '8') + string(l, '9') + string(1, '8') + string(l, '9') + string(1, '8');
            }
            const int l = n / 2 - 2;
            return string(1, '8') + string(l, '9') + string(2, '7') + string(l, '9') + string(1, '8');
        }
        const int l = n / 12, r = n % 12;
        return string(l * 6, '9') + f(r) + string(l * 6, '9');  // 999999%7 = 0
    }


