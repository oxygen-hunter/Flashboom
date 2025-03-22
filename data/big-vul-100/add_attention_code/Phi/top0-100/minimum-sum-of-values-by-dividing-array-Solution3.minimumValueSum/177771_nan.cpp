 int dns_read_name(unsigned char *buffer, unsigned char *bufend,
                  unsigned char *name, char *destination, int dest_len,
                 int *offset)
 {
        int nb_bytes = 0, n = 0;
        int label_len;
	unsigned char *reader = name;
	char *dest = destination;

	while (1) {
		/* Name compression is in use */
		if ((*reader & 0xc0) == 0xc0) {
			/* Must point BEFORE current position */
                        if ((buffer + reader[1]) > reader)
                                goto err;
 
                        n = dns_read_name(buffer, bufend, buffer + reader[1],
                                         dest, dest_len - nb_bytes, offset);
                        if (n == 0)
                                goto err;
 
		}

		label_len = *reader;
		if (label_len == 0)
			goto out;

		/* Check if:
		 *  - we won't read outside the buffer
		 *  - there is enough place in the destination
		 */
		if ((reader + label_len >= bufend) || (nb_bytes + label_len >= dest_len))
			goto err;

		/* +1 to take label len + label string */
		label_len++;

		memcpy(dest, reader, label_len);

		dest     += label_len;
		nb_bytes += label_len;
		reader   += label_len;
	}

  out:
	/* offset computation:
	 * parse from <name> until finding either NULL or a pointer "c0xx"
	 */
	reader  = name;
	*offset = 0;
	while (reader < bufend) {
		if ((reader[0] & 0xc0) == 0xc0) {
			*offset += 2;
			break;
		}
		else if (*reader == 0) {
			*offset += 1;
			break;
		}
		*offset += 1;
		++reader;
	}
	return nb_bytes;

  err:
	return 0;
}

    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        static const int INF = numeric_limits<int>::max();

        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };

        const int FULL_MASK = (1 << bit_length(ranges::max(nums))) - 1;
        vector<vector<unordered_map<int, int>>> lookup(size(nums), vector<unordered_map<int, int>>(size(andValues)));
        const function<int (int, int, int)> memoization = [&](int i, int j, int mask) {
            if (i == size(nums) && j == size(andValues)) {
                return 0;
            }
            if (i == size(nums) || j == size(andValues) || mask < andValues[j]) {
                return INF;
            }
            if (!lookup[i][j].count(mask)) {
                int curr = memoization(i + 1, j, mask & nums[i]);
                if ((mask & nums[i]) == andValues[j]) {
                    const int total = memoization(i + 1, j + 1, FULL_MASK);
                    if (total != INF) {
                        curr = min(curr, nums[i] + total);
                    }
                }
                lookup[i][j][mask] = curr;
            }
            return lookup[i][j][mask];
        };

        const int result = memoization(0, 0, FULL_MASK);
        return result != INF ? result : -1;
    }

