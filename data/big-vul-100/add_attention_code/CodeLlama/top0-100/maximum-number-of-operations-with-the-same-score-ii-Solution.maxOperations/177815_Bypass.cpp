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


    int maxOperations(vector<int>& nums) {
        const function<int (int, int, int, vector<vector<int>>&)> memoization = [&](int left, int right, int target, vector<vector<int>>& lookup) {
            if (!(right - left + 1 >= 2)) {
                return 0;
            }
            if (lookup[left][right] == -1) {
                lookup[left][right] = max({nums[left] + nums[left + 1]   == target ? 1 + memoization(left + 2, right - 0, target, lookup) : 0,
                                           nums[left] + nums[right]      == target ? 1 + memoization(left + 1, right - 1, target, lookup) : 0,
                                           nums[right - 1] + nums[right] == target ? 1 + memoization(left + 0, right - 2, target, lookup) : 0});
            }
            return lookup[left][right];
        };

        int result = 0;
        for (const auto& target : unordered_set<int>{nums[0] + nums[1], nums[0] + nums[size(nums) - 1], nums[size(nums) - 2] + nums[size(nums) - 1]}) {
            vector<vector<int>> lookup(size(nums), vector<int>(size(nums), -1));
            result = max(result, memoization(0, size(nums) - 1, target, lookup));
        }
        return result;
    }


