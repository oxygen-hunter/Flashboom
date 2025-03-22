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


    string shortestBeautifulSubstring(string s, int k) {
        const auto& check = [&](int l1, int r1, int l2, int r2) {
            const int c1 = r1 - l1 + 1, c2 = r2 -l2 + 1;
            if (c1 > c2) {
                return false;
            }
            if (c1 < c2) {
                return true;
            }
            for (int i = 0; i < c1; ++i) {
                if (s[l1 + i] != s[l2 + i]) {
                    return s[l1 + i] < s[l2 + i];
                }
            }
            return false;
        };
        
        vector<int> result = {};
        for (int right = 0, left = 0, curr = 0; right < size(s); ++right) {
            curr += static_cast<int>(s[right] == '1');
            while (curr == k + 1) {
                curr -= static_cast<int>(s[left++] == '1');
            }
            while (left < size(s) && s[left] == '0') {
                ++left;
            }
            if (curr == k) {
                if (empty(result) || check(left, right, result[0], result[1])) {
                    result = {left, right};
                }
            }
        }
        return !empty(result) ? s.substr(result[0], result[1] - result[0] + 1) : "";
    }


