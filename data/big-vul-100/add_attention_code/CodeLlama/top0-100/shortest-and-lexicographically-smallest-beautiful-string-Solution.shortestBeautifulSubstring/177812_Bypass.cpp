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


    string shortestBeautifulSubstring(string s, int k) {
        const auto& check = [&](int l1, int r1, int l2, int r2) {
            const int c1 = r1 - l1 + 1, c2 = r2 -l2 + 1;
            if (c1 > c2) {
                return false;
            }
            if (c1 < c2) {
                return true;
            }
            for (int i = 0; i < c1; ++i) {
                if (s[l1 + i] != s[l2 + i]) {
                    return s[l1 + i] < s[l2 + i];
                }
            }
            return false;
        };
        
        vector<int> result = {};
        for (int right = 0, left = 0, curr = 0; right < size(s); ++right) {
            curr += static_cast<int>(s[right] == '1');
            while (curr == k + 1) {
                curr -= static_cast<int>(s[left++] == '1');
            }
            while (left < size(s) && s[left] == '0') {
                ++left;
            }
            if (curr == k) {
                if (empty(result) || check(left, right, result[0], result[1])) {
                    result = {left, right};
                }
            }
        }
        return !empty(result) ? s.substr(result[0], result[1] - result[0] + 1) : "";
    }


