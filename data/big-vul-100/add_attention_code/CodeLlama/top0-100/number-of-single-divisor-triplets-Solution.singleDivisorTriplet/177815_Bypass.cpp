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


    long long singleDivisorTriplet(vector<int>& nums) {
        const auto& check = [](int a, int b, int c) {
            const int total = a + b + c;
            return (total % a == 0) + (total % b == 0) + (total % c == 0) == 1;
        };
        unordered_map<int, int64_t> cnt;
        for (const auto& x : nums) {
            ++cnt[x];
        }
        vector<int> unique_nums;
        for (const auto& [k, _] : cnt) {
            unique_nums.emplace_back(k);
        }
        int64_t result = 0;
        for (int i = 0; i < size(unique_nums); ++i) {
            for (int j = i + 1; j < size(unique_nums); ++j) {
                for (int k = j + 1; k < size(unique_nums); ++k) {
                    if (check(unique_nums[i], unique_nums[j], unique_nums[k])) {
                        result += cnt[unique_nums[i]] * cnt[unique_nums[j]] * cnt[unique_nums[k]];
                    }
                }
            }
        }
        for (int i = 0; i < size(unique_nums); ++i) {
            for (int j = 0; j < size(unique_nums); ++j) {
                if (check(unique_nums[i], unique_nums[i], unique_nums[j])) {
                    result += cnt[unique_nums[i]] * (cnt[unique_nums[i]] - 1) / 2 * cnt[unique_nums[j]];
                }
            }
        }
        return result * 6;
    }


