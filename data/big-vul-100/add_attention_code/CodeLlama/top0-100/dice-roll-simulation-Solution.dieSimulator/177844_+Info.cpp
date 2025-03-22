_PUBLIC_ char *strupper_talloc_n_handle(struct smb_iconv_handle *iconv_handle,
					TALLOC_CTX *ctx, const char *src, size_t n)
{
	size_t size=0;
	char *dest;

	if (!src) {
		return NULL;
	}

	/* this takes advantage of the fact that upper/lower can't
	   change the length of a character by more than 1 byte */
	dest = talloc_array(ctx, char, 2*(n+1));
	if (dest == NULL) {
		return NULL;
	}
 
        while (n-- && *src) {
                size_t c_size;
               codepoint_t c = next_codepoint_handle(iconv_handle, src, &c_size);
                src += c_size;
 
                c = toupper_m(c);
		c_size = push_codepoint_handle(iconv_handle, dest+size, c);
		if (c_size == -1) {
			talloc_free(dest);
			return NULL;
		}
		size += c_size;
	}

	dest[size] = 0;

	/* trim it so talloc_append_string() works */
	dest = talloc_realloc(ctx, dest, char, size+1);

	talloc_set_name_const(dest, dest);

	return dest;
}


    int dieSimulator(int n, vector<int>& rollMax) {
        static const int MOD = 1e9 + 7;
        vector<vector<int>> dp;
        for (int i = 0; i < 6; ++i) {
            dp.emplace_back(rollMax[i]);
            dp[i][0] = 1;  // 0-indexed
        }
        while (--n) {
            vector<vector<int>> new_dp;
            for (int i = 0; i < 6; ++i) {
                new_dp.emplace_back(rollMax[i]);  
            }
            for (int i = 0; i < 6; ++i) {
                for (int k = 0; k < rollMax[i]; ++k) {
                    for (int j = 0; j < 6; ++j) {
                        if (i == j) {
                            if (k < rollMax[i] - 1) {  // 0-indexed
                                new_dp[j][k + 1] = (new_dp[j][k + 1] + dp[i][k]) % MOD;
                            }
                        } else {
                            new_dp[j][0] = (new_dp[j][0] + dp[i][k]) % MOD;
                        }
                    }
                }
            }
            dp = move(new_dp);
        }
        uint64_t result = 0;
        for (const auto& row : dp) {
            const auto& total =
                accumulate(row.cbegin(), row.cend(),
                           0ull,
                           [&](const auto& a, const auto& b) {
                               return (a + b) % MOD;
                           });
            result = (result + total) % MOD;
        }
        return result;
    }


