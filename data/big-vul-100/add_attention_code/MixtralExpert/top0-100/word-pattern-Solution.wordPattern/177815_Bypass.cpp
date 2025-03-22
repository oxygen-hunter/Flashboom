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


    bool wordPattern(string pattern, string str) {
        // Count the words.
        int cnt = str.empty() ? 0 : 1;
        for (const auto& c : str) {
            if (c == ' ') {
                ++cnt;
            }
        }
        if (pattern.size() != cnt) {
            return false;
        }

        unordered_map<string, char> w2p;
        unordered_map<char, string> p2w;
        int i = 0, j = 0;
        for (const auto& p : pattern) {
            // Get a word at a time without saving all the words.
            j = str.find(" ", i);
            if (j == string::npos) {
                j = str.length();
            }
            const string w = str.substr(i, j - i);
    
            if (!w2p.count(w) && !p2w.count(p)) { 
                // Build mapping. Space: O(c)
                w2p[w] = p; 
                p2w[p] = w; 
            } else if (!w2p.count(w) || w2p[w] != p) {
                // Contradict mapping.
                return false;
            }
            i = j + 1;
        }
        return true;
    }


