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


    vector<int> maxUpgrades(vector<int>& count, vector<int>& upgrade, vector<int>& sell, vector<int>& money) {
        const auto& ceil_divide = [](const auto& a, const auto& b) {
            return (a + b - 1) / b ;
        };

        // let x be the number of sold servers
        // (c-x)*u <= m+(x*s)
        // x >= (c*u-m)//(u+s) <= 0
        // c-x <= c-(c*u-m)//(u+s) <= c
        vector<int> result(size(count));
        for (int i = 0; i < size(count); ++i) {
            result[i] = min(count[i] - ceil_divide(static_cast<int64_t>(count[i]) * upgrade[i] - money[i], upgrade[i] + sell[i]), static_cast<int64_t>(count[i]));
        }
        return result;
    }


