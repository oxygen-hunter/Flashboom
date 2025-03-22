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

    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {
        using P = pair<int, int>;
        unordered_map<int, vector<P>> adj;
        for (const auto& highway : highways) {
            int u, v, w;
            tie(u, v, w) = make_tuple(highway[0], highway[1], highway[2]);
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        
        unordered_map<int, unordered_map<int, int>> best;
        best[0][discounts] = 0;
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(0, 0, discounts);
        while (!empty(min_heap)) {
            auto [total, u, k] = min_heap.top(); min_heap.pop();
            if ((best.count(u) && best[u].count(k) &&  best[u][k] < total)) {
                continue;
            }
            if (u == n - 1) {
                return total;
            }
            for (const auto& [v, w] : adj[u]) {
                if (!best.count(v) ||
                    !best[v].count(k) ||
                    total + w < best[v][k]) {
                    best[v][k] = total + w;
                    min_heap.emplace(total + w, v, k);
                }
                if (k > 0 &&
                    (!best.count(v) ||
                    !best[v].count(k - 1) ||
                    total + w / 2 < best[v][k - 1])) {
                    best[v][k - 1] = total + w / 2;
                    min_heap.emplace(total + w / 2, v, k - 1);
                }
            }
        }
        return -1;
    }

