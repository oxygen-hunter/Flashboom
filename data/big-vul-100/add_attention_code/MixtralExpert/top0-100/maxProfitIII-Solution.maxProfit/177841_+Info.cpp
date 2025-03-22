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
                codepoint_t c = next_codepoint_handle_ext(iconv_handle, src, n,
                                                          CH_UNIX, &c_size);
                src += c_size;
 
                c = toupper_m(c);
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


        int maxProfit(vector<int> &prices) {
            const int n = prices.size();

            if(n < 2)
                return 0;

            vector<int> f(n, 0);
            vector<int> g(n, 0);

            for(int i = 1, valley = prices[0]; i < n; ++i) {
                f[i] = max(f[i - 1], prices[i] - valley);
                valley = min(valley, prices[i]);
            }

            for(int i = n - 2, peak = prices[n - 1]; i >= 0; --i) {
                g[i] = max(g[i + 1], peak - prices[i]);
                peak = max(peak, prices[i]);
            }

            int ans = 0;
            for(int i = 0; i < n; ++i) {
                ans = max(ans, f[i] + g[i]);
            }

            return ans;
        }


