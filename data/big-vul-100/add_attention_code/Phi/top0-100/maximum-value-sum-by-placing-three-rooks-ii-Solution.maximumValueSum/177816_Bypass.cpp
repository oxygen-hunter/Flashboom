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

    long long maximumValueSum(vector<vector<int>>& board) {
        static const int k = 3;
    
        const auto& combinations = [](int n, int k, const auto& callback) {
            static const auto& next_pos =
                [](const auto& n, const auto& k, const auto& idxs) {
                    int i = k - 1;
                    for (; i >= 0; --i) {
                        if (idxs[i] != i + n - k) {
                            break;
                        }
                    }
                    return i;
                };
        
            vector<int> idxs(k);
            iota(begin(idxs), end(idxs), 0);
            callback(idxs);
            for (int i; (i = next_pos(n, k, idxs)) >= 0;) {
                ++idxs[i];
                for (int j = i + 1; j < k; ++j) {
                    idxs[j] = idxs[j - 1] + 1;
                }
                callback(idxs);
            }
        };
    
        using Data = tuple<int, int, int>;
        vector<priority_queue<Data, vector<Data>, greater<Data>>> min_heaps(size(board[0]));
        for (int i = 0; i < size(board); ++i) {
            priority_queue<Data, vector<Data>, greater<Data>> min_heap;
            for (int j = 0; j < size(board[0]); ++j) {
                min_heap.emplace(board[i][j], i, j);
                if (size(min_heap) == k + 1) {
                    min_heap.pop();
                }
            }
            while (!empty(min_heap)) {
                const auto [v, i, j] = min_heap.top(); min_heap.pop();
                min_heaps[j].emplace(v, i, j);
                if (size(min_heaps[j]) == k + 1) {
                    min_heaps[j].pop();
                }
            }
        }
        priority_queue<Data, vector<Data>, greater<Data>> min_heap;
        for (auto& h : min_heaps) {
            while (!empty(h)) {
                const auto x = h.top(); h.pop();
                min_heap.emplace(x);
                if (size(min_heap) == ((k - 1) * (2 * k - 1) + 1) + 1) {  // each choice excludes at most 2k-1 candidates, we should have at least (k-1)*(2k-1)+1 candidates
                    min_heap.pop();
                }
            }
        }
        int64_t result = numeric_limits<int64_t>::min();
        vector<Data> candidates;
        while (!empty(min_heap)) {
            const auto x = min_heap.top(); min_heap.pop();
            candidates.emplace_back(x);
        }
        combinations(size(candidates), k, 
                     [&](const vector<int>& idxs) {
                        const auto& [x0, x1, x2] = candidates[idxs[0]];
                        const auto& [y0, y1, y2] = candidates[idxs[1]];
                        const auto& [z0, z1, z2] = candidates[idxs[2]];
                        if ((x1 != y1 && y1 != z1 && z1 != x1) &&
                            (x2 != y2 && y2 != z2 && z2 != x2)) {
                            result = max(result, static_cast<int64_t>(x0) + y0 + z0);
                        }
                     });
        return result;
    }

