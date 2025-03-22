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


    long long maxPower(vector<int>& stations, int r, int k) {
        const auto& min_power = [&]() {
            int64_t mn = numeric_limits<int64_t>::max();
            int64_t curr = accumulate(cbegin(stations), cbegin(stations) + r, 0ll);
            for (int i = 0; i < size(stations); ++i) {
                if (i + r < size(stations)) {
                    curr += stations[i + r];
                }
                if (i >= r + 1) {
                    curr -= stations[i - (r + 1)];
                }
                mn = min(mn, curr);
            }
            return mn;
        };

        const int64_t mn = min_power();
        const auto& check = [&](int64_t target) {
            vector<int> arr(cbegin(stations), cend(stations));
            int64_t curr = accumulate(cbegin(arr), cbegin(arr) + r, 0ll);
            int cnt = k;
            for (int i = 0; i < size(arr); ++i) {
                if (i + r < size(arr)) {
                    curr += arr[i + r];
                }
                if (i >= r + 1) {
                    curr -= arr[i - (r + 1)];
                }
                if (curr >= target) {
                    continue;
                }
                const auto diff = target - curr;
                if (diff > cnt) {
                    return false;
                }
                cnt -= diff;
                curr += diff;
                if (i + r < size(arr)) {
                    arr[i + r] += diff;
                }
            }
            return true;
        };

        int64_t left = mn, right = mn + k;
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (!check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return right;
    }


