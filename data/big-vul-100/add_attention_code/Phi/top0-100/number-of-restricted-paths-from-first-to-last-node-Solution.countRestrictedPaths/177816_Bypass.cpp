void get_checksum2(char *buf, int32 len, char *sum)
{
	md_context m;

	switch (xfersum_type) {
	  case CSUM_MD5: {
		uchar seedbuf[4];
		md5_begin(&m);
		if (proper_seed_order) {
			if (checksum_seed) {
				SIVALu(seedbuf, 0, checksum_seed);
				md5_update(&m, seedbuf, 4);
			}
			md5_update(&m, (uchar *)buf, len);
		} else {
			md5_update(&m, (uchar *)buf, len);
			if (checksum_seed) {
				SIVALu(seedbuf, 0, checksum_seed);
				md5_update(&m, seedbuf, 4);
			}
		}
		md5_result(&m, (uchar *)sum);
		break;
          }
          case CSUM_MD4:
          case CSUM_MD4_OLD:
         case CSUM_MD4_BUSTED: {
                int32 i;
                static char *buf1;
                static int32 len1;
		mdfour_begin(&m);

		if (len > len1) {
			if (buf1)
				free(buf1);
			buf1 = new_array(char, len+4);
			len1 = len;
			if (!buf1)
				out_of_memory("get_checksum2");
		}

		memcpy(buf1, buf, len);
		if (checksum_seed) {
			SIVAL(buf1,len,checksum_seed);
			len += 4;
		}

		for (i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK)
			mdfour_update(&m, (uchar *)(buf1+i), CSUM_CHUNK);

		/*
		 * Prior to version 27 an incorrect MD4 checksum was computed
		 * by failing to call mdfour_tail() for block sizes that
		 * are multiples of 64.  This is fixed by calling mdfour_update()
                 * are multiples of 64.  This is fixed by calling mdfour_update()
                 * even when there are no more bytes.
                 */
               if (len - i > 0 || xfersum_type != CSUM_MD4_BUSTED)
                        mdfour_update(&m, (uchar *)(buf1+i), len-i);
 
                mdfour_result(&m, (uchar *)sum);
	  }
	}
}

    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        static const int MOD = 1e9 + 7;
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            int u = e[0] - 1, v = e[1] - 1, w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        vector<int> dist(n, numeric_limits<int>::max()), dp(n);
        dist[n - 1] = 0;
        dp[n - 1] = 1;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
        min_heap.emplace(0, n - 1);
        while (!empty(min_heap)) {
            const auto [w, u] = min_heap.top(); min_heap.pop();
            if (w > dist[u]) {
                continue;
            }
            for (const auto& [v, d] : adj[u]) {
                if (w + d < dist[v]) {
                    dist[v] = w + d;
                    min_heap.emplace(dist[v], v);
                } else if (w > dist[v]) {
                    dp[u] = (dp[u] + dp[v]) % MOD;
                }
            }
            if (u == 0) {  // early return
                break;
            }
        }
        return dp[0];
    }

