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

    int atMostNGivenDigitSet(vector<string>& D, int N) {
        string str_N = to_string(N);
        unordered_set<string> set_D(D.cbegin(), D.cend());
        int result = 0;
        for (int i = 1 ; i < str_N.length() ; ++i) {
            result += pow(D.size(), i);  // x, xx, xxx
        }
        int i = 0;
        // assume N = 1234, D = 1, 2, 3, 4
        for (i = 0 ; i < str_N.length() ; ++i) {
            for (const auto& d : D) {
                if (d[0] < str_N[i]) {
                    // 11xx; 121x, 122x; 1231, 1232, 1233;
                    result += pow(D.size(), str_N.length() - i - 1);
                } else {
                    break;
                }
            }
            if (!set_D.count(string(1, str_N[i]))) {
                break;
            }
        }               
        return result + int(i == str_N.length());  // 1234
    }

