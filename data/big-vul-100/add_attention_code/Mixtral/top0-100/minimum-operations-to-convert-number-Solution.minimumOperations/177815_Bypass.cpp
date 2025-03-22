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

    int minimumOperations(vector<int>& nums, int start, int goal) {
        static const int MAX_X = 1000;

        vector<int> new_nums;
        for (const auto& y : nums) {
            if (y && ((0 <= y && y <= MAX_X) || (0 <= (goal - y) && (goal - y) <= MAX_X) || (0 <= (goal + y) && (goal + y) <= MAX_X) || (0 <= (goal ^ y) && (goal ^ y) <= MAX_X))) {
                new_nums.emplace_back(y);
            }
        }
        nums = move(new_nums);
        vector<pair<int, int>> q = {{start, 0}};
        unordered_set<int> lookup = {start};
        while (!empty(q)) {
            vector<pair<int, int>> new_q;
            for (const auto& [x, steps] : q) {
                for (const auto& y : nums) {
                    for (const auto& nx : {x + y, x - y, x ^ y}) {
                        if (nx == goal) {
                            return steps + 1;
                        }
                        if (!(0 <= nx && nx <= MAX_X) || lookup.count(nx)) {
                            continue;
                        }
                        lookup.emplace(nx);
                        new_q.emplace_back(nx, steps + 1);
                    }
                }
            }
            q = move(new_q);
        }
        return -1;
    }

