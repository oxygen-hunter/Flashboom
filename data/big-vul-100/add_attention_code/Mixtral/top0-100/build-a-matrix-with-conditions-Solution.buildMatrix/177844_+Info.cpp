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

    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        const auto& topological_sort = [&](const auto& conditions) {
            vector<vector<int>> adj(k);
            vector<int> in_degree(k);
            for (const auto& c : conditions) {
                const int u = c[0] - 1, v = c[1] - 1;
                adj[u].emplace_back(v);
                ++in_degree[v];
            }
            vector<int> result;
            vector<int> q;
            for (int u = 0; u < k; ++u) {
                if (!in_degree[u]) {
                    q.emplace_back(u);
                }
            }
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    result.emplace_back(u);
                    for (const auto& v : adj[u]) {
                        --in_degree[v];
                        if (in_degree[v]) {
                            continue;
                        }
                        new_q.emplace_back(v);
                    }
                }
                q = move(new_q);
            }
            return result;
        };

        const auto& row_order = topological_sort(rowConditions);
        if (size(row_order) != k) {
            return {};
        }
        const auto& col_order = topological_sort(colConditions);
        if (size(col_order) != k) {
            return {};
        }
        vector<int> row_idx(k);
        for (int i = 0; i < k; ++i) {
            row_idx[row_order[i]] = i;
        }
        vector<int> col_idx(k);
        for (int i = 0; i < k; ++i) {
            col_idx[col_order[i]] = i;
        }
        vector<vector<int>> result(k, vector<int>(k));
        for (int i = 0; i < k; ++i) {
            result[row_idx[i]][col_idx[i]] = i + 1;
        }
        return result;
    }

