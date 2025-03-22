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


    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        const auto R = board.size(), C = board[0].size();
        bool changed = true;
        
        while (changed) {
            changed = false;
            
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c + 2 < C; ++c) {
                    auto v = abs(board[r][c]);
                    if (v != 0 && v == abs(board[r][c + 1]) && v == abs(board[r][c + 2])) {
                        board[r][c] = board[r][c + 1] = board[r][c + 2] = -v;
                        changed = true;
                    }
                }
            }
            
            for (int r = 0; r + 2 < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    auto v = abs(board[r][c]);
                    if (v != 0 && v == abs(board[r + 1][c]) && v == abs(board[r + 2][c])) {
                        board[r][c] = board[r + 1][c] = board[r + 2][c] = -v;
                        changed = true;
                    }
                }
            }

            for (int c = 0; c < C; ++c) {
                int empty_r = R - 1;
                for (int r = R - 1; r >= 0; --r) {
                    if (board[r][c] > 0) {
                        board[empty_r--][c] = board[r][c];
                    }
                }
                for (int r = empty_r; r >= 0; --r) {
                    board[r][c] = 0;
                }
            }
        }
        
        return board;
    }


