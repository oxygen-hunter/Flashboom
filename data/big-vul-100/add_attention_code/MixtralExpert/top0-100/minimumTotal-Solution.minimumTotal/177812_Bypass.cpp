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


        int minimumTotal(vector<vector<int> > &triangle) {
            const int N = triangle.size();
            vector<int> f(N, INT_MAX);
            int ans = INT_MAX;

            f[0] = triangle[0][0];
            for(int i = 1; i < N; ++i) {
                for(int j = i; j > 0; --j) {
                    f[j] = min(f[j], f[j - 1]) + triangle[i][j];
                }
                f[0] += triangle[i][0];
            }

            for(int i = 0; i < N; ++i) {
                ans = min(ans, f[i]);
            }

            return ans;
        }


