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

    bool queryString(string S, int N) {
        // since S with length n has at most different n-k+1 k-digit numbers
        // => given S with length n, valid N is at most 2(n-k+1)
        // => valid N <= 2(n-k+1) < 2n = 2 * S.length
        for (int i = N; i > N / 2; --i) {
            // if bin_i is a substring of S, bin_i/2 is too
            const auto& b = bitset<32>(i).to_string();
            if (S.find(b.substr(b.find("1"))) == string::npos) {
                return false;
            }
        }
        return true;
    }

