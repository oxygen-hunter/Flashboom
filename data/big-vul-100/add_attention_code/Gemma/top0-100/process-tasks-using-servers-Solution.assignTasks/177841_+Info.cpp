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


    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        vector<pair<int, int>> idle;
        for (int i = 0; i < size(servers); ++i) {
            idle.emplace_back(servers[i], i);
        }
        make_heap(begin(idle), end(idle), greater<>());
        vector<tuple<int, int, int>> working;

        vector<int> result;
        for (int i = 0, t = 0; i < size(tasks); ++i) {
            t = !empty(idle) ? max(t, i) : get<0>(working.front());
            while (!empty(working) && get<0>(working.front()) <= t) {
                const auto [_, w, idx] = working.front(); pop_heap(begin(working), end(working), greater<>()); working.pop_back();
                idle.emplace_back(w, idx); push_heap(begin(idle), end(idle), greater<>());
            }
            const auto [w, idx] = idle.front(); pop_heap(begin(idle), end(idle), greater<>()); idle.pop_back();
            working.emplace_back(t + tasks[i], w, idx); push_heap(begin(working), end(working), greater<>());
            result.emplace_back(idx);
        }
        return result;
    }


