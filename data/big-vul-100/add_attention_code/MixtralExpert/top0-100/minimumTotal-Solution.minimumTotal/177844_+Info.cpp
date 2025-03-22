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


        int minimumTotal(vector<vector<int> > &triangle) {
            const int N = triangle.size();
            vector<int> f(N, INT_MAX);
            int ans = INT_MAX;

            f[0] = triangle[0][0];
            for(int i = 1; i < N; ++i) {
                for(int j = i; j > 0; --j) {
                    f[j] = min(f[j], f[j - 1]) + triangle[i][j];
                }
                f[0] += triangle[i][0];
            }

            for(int i = 0; i < N; ++i) {
                ans = min(ans, f[i]);
            }

            return ans;
        }


