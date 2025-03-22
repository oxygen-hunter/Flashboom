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

    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        const auto& check = [&](int i, int j) {
            for (int ni = i - 1; ni <= i; ++ni) {
                for (int nj = j - 1; nj <= j + 1; ++nj) {
                    if (abs(image[ni][nj] - image[ni + 1][nj]) > threshold) {
                        return false;
                    }
                }
            }
            for (int ni = i - 1; ni <= i + 1; ++ni) {
                for (int nj = j - 1; nj <= j; ++nj) {
                    if (abs(image[ni][nj] - image[ni][nj + 1]) > threshold) {
                        return false;
                    }
                }
            }
            return true;
        };
    
        vector<vector<int>> result(size(image), vector<int>(size(image[0])));
        vector<vector<int>> cnt(size(image), vector<int>(size(image[0])));
        for (int i = 1; i + 1 < size(image); ++i) {
            for (int j = 1; j + 1 < size(image[0]); ++j) {
                if (!check(i, j)) {
                    continue;
                }
                int total = 0;
                for (int ni = i - 1; ni <= i + 1; ++ni) {
                    for (int nj = j - 1; nj <= j + 1; ++nj) {
                        total += image[ni][nj];
                    }
                }
                total /= 9;
                for (int ni = i - 1; ni <= i + 1; ++ni) {
                    for (int nj = j - 1; nj <= j + 1; ++nj) {
                        ++cnt[ni][nj];
                        result[ni][nj] += total;
                    }
                }
            }
        }
        for (int i = 0; i < size(image); ++i) {
            for (int j = 0; j < size(image[0]); ++j) {
                if (cnt[i][j]) {
                    result[i][j] /= cnt[i][j];
                } else {
                    result[i][j] = image[i][j];
                }
            }
        }
        return result;
    }

