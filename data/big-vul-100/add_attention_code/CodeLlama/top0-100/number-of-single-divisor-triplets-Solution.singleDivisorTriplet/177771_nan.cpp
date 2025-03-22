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


    long long singleDivisorTriplet(vector<int>& nums) {
        const auto& check = [](int a, int b, int c) {
            const int total = a + b + c;
            return (total % a == 0) + (total % b == 0) + (total % c == 0) == 1;
        };
        unordered_map<int, int64_t> cnt;
        for (const auto& x : nums) {
            ++cnt[x];
        }
        vector<int> unique_nums;
        for (const auto& [k, _] : cnt) {
            unique_nums.emplace_back(k);
        }
        int64_t result = 0;
        for (int i = 0; i < size(unique_nums); ++i) {
            for (int j = i + 1; j < size(unique_nums); ++j) {
                for (int k = j + 1; k < size(unique_nums); ++k) {
                    if (check(unique_nums[i], unique_nums[j], unique_nums[k])) {
                        result += cnt[unique_nums[i]] * cnt[unique_nums[j]] * cnt[unique_nums[k]];
                    }
                }
            }
        }
        for (int i = 0; i < size(unique_nums); ++i) {
            for (int j = 0; j < size(unique_nums); ++j) {
                if (check(unique_nums[i], unique_nums[i], unique_nums[j])) {
                    result += cnt[unique_nums[i]] * (cnt[unique_nums[i]] - 1) / 2 * cnt[unique_nums[j]];
                }
            }
        }
        return result * 6;
    }


