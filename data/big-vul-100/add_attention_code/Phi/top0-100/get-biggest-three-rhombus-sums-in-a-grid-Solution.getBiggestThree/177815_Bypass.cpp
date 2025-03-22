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

    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        static const int K = 3;

        vector<vector<int>> left{grid}, right{grid};
        for (int i = 1; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]) - 1; ++j) {
                left[i][j] += left[i - 1][j + 1];
            }
        }
        for (int i = 1; i < size(grid); ++i) {
            for (int j = 1; j < size(grid[0]); ++j) {
                right[i][j] += right[i - 1][j - 1];
            }
        }
        priority_queue<int, vector<int>, greater<int>> min_heap;
        unordered_set<int> lookup;
        for (int k = 0; k <= (min(size(grid), size(grid[0])) + 1) / 2; ++k) {
            for (int i = k; i < size(grid) - k; ++i) {
                for (int j = k; j < size(grid[0]) - k; ++j) {
                    int total = k ? ((left[i][j - k] - left[i - k][j]) + (right[i][j + k] - right[i - k][j]) + grid[i - k][j]) +  
                                    ((left[i + k][j] - left[i][j + k]) + (right[i + k][j] - right[i][j - k]) - grid[i + k][j])
                                  : grid[i][j];
                    if (lookup.count(total)) {
                        continue;
                    }
                    lookup.emplace(total);
                    min_heap.emplace(total);
                    if (size(min_heap) == K + 1) {
                        lookup.erase(min_heap.top()); min_heap.pop();
                    }
                }
            }
        }
        vector<int> result;
        while (!empty(min_heap)) {
            result.emplace_back(min_heap.top()); min_heap.pop();
        }
        reverse(begin(result), end(result));
        return result;
    }

