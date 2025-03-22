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


    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        static const int MOD = 1e9 + 7;

        priority_queue<vector<int>> buy;  // max_heap
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> sell;  // min_heap
        for (const auto& o : orders) {
            if (o[2] == 0) {
                buy.emplace(o);
            } else {
                sell.emplace(o);
            }
            while (!empty(buy) && !empty(sell) && sell.top()[0] <= buy.top()[0]) {
                int k = min(buy.top()[1], sell.top()[1]);
                auto tmp = buy.top(); buy.pop();
                tmp[1] -= k;
                if (tmp[1]) {
                    buy.emplace(tmp);
                }
                tmp = sell.top(); sell.pop();
                tmp[1] -= k;
                if (tmp[1]) {
                    sell.emplace(tmp);
                }
            }

        }
        int result = 0;
        while (!empty(buy)) {
            result = (result + buy.top()[1]) % MOD; buy.pop();
        }
        while (!empty(sell)) {
            result = (result + sell.top()[1]) % MOD; sell.pop();
        }
        return result;
    }


