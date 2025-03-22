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

    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        static const auto& choice_mask =
            [](const auto& nums, const auto& idxs) {
                return accumulate(cbegin(idxs), cend(idxs), 0,
                                  [&nums](const auto& a, const auto& b) {
                                      return a | (1 << nums[b]);
                                  });
            };
        static const auto& next_pos =
            [](const auto& n, const auto& r, const auto& idxs) {
                int i = r - 1;
                for (; i >= 0; --i) {
                    if (idxs[i] != i + n - r) {
                        break;
                    }
                }
                return i;
            };

        vector<int> reqs(n);
        for (const auto& d : dependencies) {
            reqs[d[1] - 1] |= 1 << (d[0] - 1);
        }
        vector<int> dp(1 << n, n);
        dp[0] = 0;
        for (int mask = 0; mask < dp.size(); ++mask) {
            vector<int> candidates;
            for (int v = 0; v < n; ++v) {
                if ((mask & (1 << v)) == 0 && (mask & reqs[v]) == reqs[v]) {
                    candidates.emplace_back(v);
                }
            }
            const auto r = min(int(candidates.size()), k);
            vector<int> idxs(r);
            iota(begin(idxs), end(idxs), 0);
            const auto& new_mask = (mask | choice_mask(candidates, idxs));
            dp[new_mask] = min(dp[new_mask], dp[mask] + 1);
            for (int i; (i = next_pos(candidates.size(), r, idxs)) >= 0;) {
                ++idxs[i];
                for (int j = i + 1; j < k; ++j) {
                    idxs[j] = idxs[j - 1] + 1;
                }
                const auto& new_mask = (mask | choice_mask(candidates, idxs));
                dp[new_mask] = min(dp[new_mask], dp[mask] + 1);
            }
        }
        return dp.back();
    }

