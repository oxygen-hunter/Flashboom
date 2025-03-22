 _PUBLIC_ codepoint_t next_codepoint_handle_ext(
                        struct smb_iconv_handle *ic,
                       const char *str, charset_t src_charset,
                        size_t *bytes_consumed)
 {
        /* it cannot occupy more than 4 bytes in UTF16 format */
	smb_iconv_t descriptor;
	size_t ilen_orig;
	size_t ilen;
	size_t olen;
	char *outbuf;

	if ((str[0] & 0x80) == 0) {
		*bytes_consumed = 1;
		return (codepoint_t)str[0];
	}

	/*
	 * we assume that no multi-byte character can take more than 5 bytes.
         * we assume that no multi-byte character can take more than 5 bytes.
         * This is OK as we only support codepoints up to 1M (U+100000)
         */
       ilen_orig = strnlen(str, 5);
        ilen = ilen_orig;
 
        descriptor = get_conv_handle(ic, src_charset, CH_UTF16);
		*bytes_consumed = 1;
		return INVALID_CODEPOINT;
	}


    int shortestPathWithHops(int n, vector<vector<int>>& edges, int s, int d, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
            adj[e[1]].emplace_back(e[0], e[2]);
        }
        const auto& modified_dijkstra = [&]() {
            static const int INF = numeric_limits<int>::max();

            vector<vector<int>> best(size(adj), vector<int>(k + 1, INF));
            best[s][0] = 0;
            priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> min_heap;
            min_heap.emplace(best[s][0], s, 0);
            while (!empty(min_heap)) {
                const auto [curr, u, cnt] = min_heap.top(); min_heap.pop();
                if (curr > best[u][cnt]) {
                    continue;
                }
                if (u == d) {
                    return curr;
                }
                for (const auto& [v, w] : adj[u]) {
                    if (w < best[v][cnt] - curr) {
                        best[v][cnt] = curr + w;
                        min_heap.emplace(best[v][cnt], v, cnt);
                    }
                    if (cnt + 1 <= k && curr < best[v][cnt + 1]) {
                        best[v][cnt + 1] = curr;
                        min_heap.emplace(best[v][cnt + 1], v, cnt + 1);
                    }
                }
            }
            return -1;
        };

        return modified_dijkstra();
    }


