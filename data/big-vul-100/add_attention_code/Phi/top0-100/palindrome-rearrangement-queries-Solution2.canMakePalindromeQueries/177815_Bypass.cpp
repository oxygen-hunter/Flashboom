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

    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        vector<int> prefix(size(s) / 2 + 1);
        vector<vector<int>> prefixs1(size(s) / 2 + 1, vector<int>(26));
        vector<vector<int>> prefixs2(size(s) / 2 + 1, vector<int>(26));
        for (int i = 0; i < size(s) / 2; ++i) {
            const int x = s[i] - 'a', y = s[(size(s) - 1) - i] - 'a';
            prefix[i + 1] = prefix[i] + (x != y ? 1 : 0);
            for (int j = 0; j < 26; ++j) {
                prefixs1[i + 1][j] = prefixs1[i][j] + (j == x ? 1 : 0);
                prefixs2[i + 1][j] = prefixs2[i][j] + (j == y ? 1 : 0);
            }
        }
    
        const auto& check = [&](int left1, int right1, int left2, int right2) {
            const auto& same = [&](int left, int right) {
                for (int i = 0; i < 26; ++i) {
                    if ((prefixs1[right + 1][i] - prefixs1[left][i]) - (prefixs2[right + 1][i] - prefixs1[left][i]) != 0) {
                        return false;
                    }
                }
                return true;
            };

            const auto& min_left = min(left1, left2), &max_left = max(left1, left2);
            const auto& min_right = min(right1, right2), &max_right = max(right1, right2);
            if (!(prefix[min_left] - prefix[0] == 0 && prefix.back() - prefix[max_right + 1] == 0)) {
                return false;
            }
            if (min_right < max_left) {  // non-overlapped
                return prefix[max_left] - prefix[min_right + 1] == 0 && same(min_left, min_right) && same(max_left, max_right);
            }
            // overlapped
            if ((left1 == min_left) == (right1 == max_right)) {  // inside another
                return same(min_left, max_right);
            }
            // not inside another
            auto p1 = &prefixs1, p2 = &prefixs2;
            if (min_left != left1) {
                swap(p1, p2);
            }
            for (int i = 0; i < 26; ++i) {
                const int d1 = ((*p1)[min_right + 1][i] - (*p1)[min_left][i]) - ((*p2)[max_left][i] - (*p2)[min_left][i]);
                const int d2 = ((*p2)[max_right + 1][i] - (*p2)[max_left][i]) - ((*p1)[max_right + 1][i] - (*p1)[min_right + 1][i]);
                if (!(d1 == d2 && d1 >= 0)) {  // test case: s = "aabbba", queries = [[0,1,3,4]]
                    return false;
                }
            }
            return true;
        };
    
        vector<bool> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = check(queries[i][0], queries[i][1], (size(s) - 1) - queries[i][3], (size(s) - 1) - queries[i][2]);
        }
        return result;
    }

