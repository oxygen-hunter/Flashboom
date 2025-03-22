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

    int maximumMinutes(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> directions{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        enum State {FIRE = 1, WALL, PERSON};
        const int INF = 1e9;
        const auto& bfs = [&]() {
            unordered_map<int, vector<vector<int>>> time;
            time[FIRE] = vector<vector<int>>(size(grid), vector<int>(size(grid[0]), INF));
            time[PERSON] = vector<vector<int>>(size(grid), vector<int>(size(grid[0]), INF));
            vector<tuple<int, int, int>> q;
            for (int r = 0; r < size(grid); ++r) {
                for (int c = 0; c < size(grid[0]); ++c) {
                    if (grid[r][c] == FIRE) {
                        q.emplace_back(r, c, FIRE);
                    }
                }
            }
            q.emplace_back(0, 0, PERSON);
            for (const auto& [r, c, t] : q) {
                time[t][r][c] = 0;
            }
            for (int d = 0; !empty(q); ++d) {
                vector<tuple<int, int, int>> new_q;
                for (const auto& [r, c, t] : q) {
                    for (const auto& [dr, dc] : directions) {
                        const int nr = r + dr, nc = c + dc;
                        if (!(0 <= nr && nr < size(grid) && 0 <= nc && nc < size(grid[0]) &&
                              grid[nr][nc] != WALL && time[t][nr][nc] == INF &&
                              (t == FIRE ||
                               d + 1 < time[FIRE][nr][nc] || (d + 1 == time[FIRE][nr][nc] && nr == size(grid) - 1 && nc == size(grid[0]) - 1)))) {
                            continue;
                        }
                        time[t][nr][nc] = d + 1;
                        new_q.emplace_back(nr, nc, t);
                    }
                }
                q = move(new_q);
            }
            return time;
        };
        auto time = bfs();
        if (time[PERSON][size(grid) - 1][size(grid[0]) - 1] == INF) {
            return -1;
        }
        if (time[FIRE][size(grid) - 1][size(grid[0]) - 1] == INF) {
            return INF;
        }
        const int diff = time[FIRE][size(grid) - 1][size(grid[0]) - 1] - time[PERSON][size(grid) - 1][size(grid[0]) - 1];
        return (time[FIRE][size(grid) - 1][size(grid[0]) - 2] - time[PERSON][size(grid) - 1][size(grid[0]) - 2] == diff + 2 ||
                time[FIRE][size(grid) - 2][size(grid[0]) - 1] - time[PERSON][size(grid) - 2][size(grid[0]) - 1] == diff + 2)
               ? diff
               : diff - 1;
    }

