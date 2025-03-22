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

    vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
        static const unordered_map<char, pair<int, int>> directions = {
            {'U', {-1, 0}}, {'R', {0, 1}}, {'D', {1, 0}}, {'L', {0, -1}}
        };

        int x0 = startPos[0], y0 = startPos[1];
        int x = 0, y = 0;
        vector<int> result(size(s));
        iota(rbegin(result), rend(result), 1);
        unordered_map<int, vector<int>> lookup_x, lookup_y;
        lookup_x[x0 - x].emplace_back(0);
        lookup_y[y0 - y].emplace_back(0);
        for (int i = 0; i < size(s); ++i) {
            const auto& [dx, dy] = directions.at(s[i]);
            x += dx, y += dy;
            for (const auto& k : {n - x, -x - 1}) {
                if (!lookup_x.count(k)) {
                    continue;
                }
                for (const auto& j : lookup_x[k]) {
                    result[j] = min(result[j], i - j);
                }
                lookup_x.erase(k);
            }
            for (const auto& k : {n - y, -y - 1}) {
                if (!lookup_y.count(k)) {
                    continue;
                }
                for (const auto& j : lookup_y[k]) {
                    result[j] = min(result[j], i - j);
                }
                lookup_y.erase(k);
            }
            lookup_x[x0 - x].emplace_back(i + 1);
            lookup_y[y0 - y].emplace_back(i + 1);
        }
        return result;
    }

