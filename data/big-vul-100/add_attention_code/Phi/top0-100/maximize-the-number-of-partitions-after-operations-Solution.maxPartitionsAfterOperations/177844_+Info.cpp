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

    int maxPartitionsAfterOperations(string s, int k) {
        vector<int> left(size(s) + 1);
        vector<int> left_mask(size(s) + 1);
        for (int i = 0, cnt = 0, mask = 0; i < size(s); ++i) {
            mask |= 1 << (s[i] - 'a');
            if (__builtin_popcount(mask) > k) {
                ++cnt;
                mask = 1 << (s[i] - 'a');
            }
            left[i + 1] = cnt;
            left_mask[i + 1] = mask;
        }
        vector<int> right(size(s) + 1);
        vector<int> right_mask(size(s) + 1);
        for (int i = size(s) - 1, cnt = 0, mask = 0; i >= 0; --i) {
            mask |= 1 << (s[i] - 'a');
            if (__builtin_popcount(mask) > k) {
                ++cnt;
                mask = 1 << (s[i] - 'a');
            }
            right[i] = cnt;
            right_mask[i] = mask;
        }

        int result = 0;
        for (int i = 0; i < size(s); ++i) {
            int curr = left[i] + right[i + 1];
            const int mask = left_mask[i] | right_mask[i + 1];
            if (__builtin_popcount(left_mask[i]) == k && __builtin_popcount(right_mask[i + 1]) == k && __builtin_popcount(mask) != 26) {
                curr += 3;
            } else if (__builtin_popcount(mask) + (__builtin_popcount(mask) != 26 ? 1 : 0) > k) {  // test case: s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", k = 26
                curr += 2;
            } else {
                curr += 1;
            }
            result = max(result, curr);
        }
        return result;
    }

