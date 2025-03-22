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

    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        static const auto NEG_INF = numeric_limits<int64_t>::min();

        unordered_set<int> vals_set;
        for (int i = 0; i < size(nums); ++i) {
            vals_set.emplace(nums[i] - i);
        }
        vector<int> sorted_vals(cbegin(vals_set), cend(vals_set));
        sort(begin(sorted_vals), end(sorted_vals));
        unordered_map<int, int> val_to_idx;
        for (int i = 0; i < size(sorted_vals); ++i) {
            val_to_idx[sorted_vals[i]] = i;
        }
        SegmentTree<int64_t> st(size(val_to_idx));
        for (int i = 0; i < size(nums); ++i) {
            const auto val = max(st.query(0, val_to_idx[nums[i] - i]), static_cast<int64_t>(0)) + nums[i];
            st.update(val_to_idx[nums[i] - i], val);
        }
        return st.query(0, size(val_to_idx) - 1);
    }

