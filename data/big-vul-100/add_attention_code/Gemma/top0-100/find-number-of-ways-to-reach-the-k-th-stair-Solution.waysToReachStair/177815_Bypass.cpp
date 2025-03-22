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


    int waysToReachStair(int k) {
        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };

        const auto& ceil_log2_x = [&](int x) {
            return bit_length(x - 1);
        };
    
        int l = ceil_log2_x(k);
        for (; (1ll << l) - k <= l + 1; ++l);
        vector<__int128> fact(l + 1, 1);
        for (int i = 0; i + 1 < size(fact); ++i) {
            fact[i + 1] = fact[i] * (i + 1);
        }
        const auto& nCr = [&](int n, int r) {
            if (!(0 <= r && r <= n)) {
                return static_cast<__int128>(0);
            }
            return fact[n] / fact[r] / fact[n - r];
        };

        int result = 0;
        for (int i = 0; i < l; ++i) {
            result += nCr(i + 1, (1 << i) - k);
        }
        return result;
    }


