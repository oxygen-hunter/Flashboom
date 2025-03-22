void file_checksum(const char *fname, const STRUCT_STAT *st_p, char *sum)
{
	struct map_struct *buf;
	OFF_T i, len = st_p->st_size;
	md_context m;
	int32 remainder;
	int fd;

	memset(sum, 0, MAX_DIGEST_LEN);

	fd = do_open(fname, O_RDONLY, 0);
	if (fd == -1)
		return;

	buf = map_file(fd, len, MAX_MAP_SIZE, CSUM_CHUNK);

	switch (checksum_type) {
	  case CSUM_MD5:
		md5_begin(&m);

		for (i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
			md5_update(&m, (uchar *)map_ptr(buf, i, CSUM_CHUNK),
				   CSUM_CHUNK);
		}

		remainder = (int32)(len - i);
		if (remainder > 0)
			md5_update(&m, (uchar *)map_ptr(buf, i, remainder), remainder);

		md5_result(&m, (uchar *)sum);
		break;
	  case CSUM_MD4:
          case CSUM_MD4:
          case CSUM_MD4_OLD:
          case CSUM_MD4_BUSTED:
                mdfour_begin(&m);
 
                for (i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
		}

		/* Prior to version 27 an incorrect MD4 checksum was computed
		 * by failing to call mdfour_tail() for block sizes that
		 * are multiples of 64.  This is fixed by calling mdfour_update()
		 * even when there are no more bytes. */
                 * are multiples of 64.  This is fixed by calling mdfour_update()
                 * even when there are no more bytes. */
                remainder = (int32)(len - i);
               if (remainder > 0 || checksum_type != CSUM_MD4_BUSTED)
                        mdfour_update(&m, (uchar *)map_ptr(buf, i, remainder), remainder);
 
                mdfour_result(&m, (uchar *)sum);
		rprintf(FERROR, "invalid checksum-choice for the --checksum option (%d)\n", checksum_type);
		exit_cleanup(RERR_UNSUPPORTED);
	}

	close(fd);
	unmap_file(buf);
}


    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        vector<vector<unordered_set<int>>> neighbors(n, vector<unordered_set<int>>(2));
        for (const auto& edge : red_edges) {
            neighbors[edge[0]][0].emplace(edge[1]);
        }
        for (const auto& edge : blue_edges) {
            neighbors[edge[0]][1].emplace(edge[1]);
        }
        const auto& INF = max(2 * n - 3, 0) + 1;
        vector<vector<int>> dist(n, vector<int>(2, INF));
        dist[0] = {0, 0};
        queue<pair<int, int>> q({{0, 0}, {0, 1}});
        while (!q.empty()) {
            int i, c;
            tie(i, c) = q.front(); q.pop();
            for (const auto& j : neighbors[i][c]) {
                if (dist[j][c] != INF) {
                    continue;
                }
                dist[j][c] = dist[i][1 ^ c] + 1;
                q.emplace(j, 1 ^ c);
            }
        }
        vector<int> result;
        for (const auto& d : dist) {
            const auto& x = *min_element(d.cbegin(), d.cend());
            result.emplace_back((x != INF) ? x : -1);
        }
        return result;
    }


