void GfxImageColorMap::getRGBLine(Guchar *in, unsigned int *out, int length) {
  int i, j;
  Guchar *inp, *tmp_line;

   switch (colorSpace->getMode()) {
   case csIndexed:
   case csSeparation:
    tmp_line = (Guchar *) gmalloc (length * nComps2);
     for (i = 0; i < length; i++) {
       for (j = 0; j < nComps2; j++) {
 	tmp_line[i * nComps2 + j] = byte_lookup[in[i] * nComps2 + j];
      }
    }
    colorSpace2->getRGBLine(tmp_line, out, length);
    gfree (tmp_line);
    break;

  default:
    inp = in;
    for (j = 0; j < length; j++)
      for (i = 0; i < nComps; i++) {
	*inp = byte_lookup[*inp * nComps + i];
	inp++;
      }
    colorSpace->getRGBLine(in, out, length);
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


