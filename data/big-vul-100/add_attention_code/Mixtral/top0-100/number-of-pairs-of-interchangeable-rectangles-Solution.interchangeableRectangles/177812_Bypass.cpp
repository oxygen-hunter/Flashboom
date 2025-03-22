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

    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        unordered_map<int, unordered_map<int, int>> lookup;
        for (const auto& rect : rectangles) {
            const int g = gcd(rect[0], rect[1]);  // Time: O(logx) ~= O(1)
            ++lookup[rect[0] / g][rect[1] / g];
        }
        int64_t result = 0;
        for (const auto& [_, kvp] : lookup) {
            for (const auto& [_, c] : kvp) {
                result += static_cast<int64_t>(c) * (c - 1) / 2;
            }
        }
        return result;
    }

