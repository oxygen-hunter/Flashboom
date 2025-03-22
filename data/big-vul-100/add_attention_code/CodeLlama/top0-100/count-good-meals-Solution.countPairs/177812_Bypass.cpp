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


    int countPairs(vector<int>& deliciousness) {
        static const int MOD = 1e9 + 7;

        static const auto& floor_log2_x = [](int x) {
            return 8 * sizeof(int) - __builtin_clz(x) - 1;
        };
        
        int max_pow = floor_log2_x(*max_element(cbegin(deliciousness),
                                                cend(deliciousness))) + 1;
        unordered_map<int, int> cnt;
        int result = 0;
        for (const auto& d : deliciousness) {
            int p = 1;
            for (int i = 0; i <= max_pow; ++i) {
                result = (result + cnt[p - d]) % MOD;
                p <<= 1;
            }
            ++cnt[d];
        }
        return result;
    }


