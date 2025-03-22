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


    int minSwapsCouples(vector<int>& row) {
        int N = row.size() / 2;
        vector<vector<int>> couples(N);
        for (int seat = 0; seat < row.size(); ++seat) {
            couples[row[seat] / 2].emplace_back(seat / 2);
        }
        vector<vector<int>> adj(N);
        for (const auto& couple : couples) {
            adj[couple[0]].emplace_back(couple[1]);
            adj[couple[1]].emplace_back(couple[0]);
        }
        
        int result = 0;
        for (int couch = 0; couch < N; ++couch) {
            if (adj[couch].empty()) {
                continue;
            }
            int couch1 = couch;
            int couch2 = adj[couch1].back(); adj[couch1].pop_back();
            while (couch2 != couch) {
                ++result;
                adj[couch2].erase(find(adj[couch2].begin(), adj[couch2].end(), couch1));
                couch1 = couch2;
                couch2 = adj[couch1].back(); adj[couch1].pop_back();
            }
        }
        return result;  // also equals to N - (# of cycles)
    }


