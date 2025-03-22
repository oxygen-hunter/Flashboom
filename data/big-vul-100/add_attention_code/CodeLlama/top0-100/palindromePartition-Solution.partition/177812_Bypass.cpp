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


        vector<vector<string> > partition(string s) {
            const int n = s.size();
            bool p[n][n];

            fill_n(&p[0][0], n * n, false);

            for (int i = n - 1; i >= 0; --i)
                for (int j = i; j < n; ++j)
                    p[i][j] = s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1]);

            vector<vector<string> > sub_palins[n];
            for (int i = n - 1; i >= 0; --i) {
                for (int j = i; j < n; ++j)
                    if (p[i][j]) {
                        const string palindrome = s.substr(i, j - i + 1);
                        if (j + 1 < n) {
                            for (auto v : sub_palins[j + 1]) {
                                v.insert(v.begin(), palindrome);
                                sub_palins[i].push_back(v);
                            }
                        } 
                        else {
                            sub_palins[i].push_back(vector<string> { palindrome });
                        }
                    }
            }

            return sub_palins[0];
        }


