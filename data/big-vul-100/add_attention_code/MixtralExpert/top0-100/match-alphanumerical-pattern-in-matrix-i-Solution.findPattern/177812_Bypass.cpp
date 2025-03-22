void sum_update(const char *p, int32 len)
{
	switch (cursum_type) {
	  case CSUM_MD5:
		md5_update(&md, (uchar *)p, len);
		break;
          case CSUM_MD4:
          case CSUM_MD4_OLD:
          case CSUM_MD4_BUSTED:
                if (len + sumresidue < CSUM_CHUNK) {
                        memcpy(md.buffer + sumresidue, p, len);
                        sumresidue += len;
		}

		if (sumresidue) {
			int32 i = CSUM_CHUNK - sumresidue;
			memcpy(md.buffer + sumresidue, p, i);
			mdfour_update(&md, (uchar *)md.buffer, CSUM_CHUNK);
			len -= i;
			p += i;
		}

		while (len >= CSUM_CHUNK) {
			mdfour_update(&md, (uchar *)p, CSUM_CHUNK);
			len -= CSUM_CHUNK;
			p += CSUM_CHUNK;
		}

		sumresidue = len;
		if (sumresidue)
			memcpy(md.buffer, p, sumresidue);
		break;
	  case CSUM_NONE:
		break;
	}
}


    vector<int> findPattern(vector<vector<int>>& board, vector<string>& pattern) {
        const auto& check = [&](int i, int j) {
            vector<int> lookup(26, -1);
            vector<bool> lookup2(10);
            for (int r = 0; r < size(pattern); ++r) {
                for (int c = 0; c < size(pattern[0]); ++c) {
                    const int y = board[i + r][j + c];
                    if (isdigit(pattern[r][c])) {
                        if (pattern[r][c] - '0' != y) {
                            return false;
                        }
                        continue;
                    }
                    const int x = pattern[r][c] - 'a';
                    if (lookup[x] == -1) {
                        if (lookup2[y]) {
                            return false;
                        }
                        lookup2[y] = true;
                        lookup[x] = y;
                        continue;
                    }
                    if (lookup[x] != y) {
                        return false;
                    }
                }
            }
            return true;
        };
    
        for (int i = 0; i + size(pattern) - 1 < size(board); ++i) {
            for (int j = 0; j + size(pattern[0]) - 1 < size(board[0]); ++j) {
                if (check(i, j)) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }


