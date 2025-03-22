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


    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        static const int MOD = 1e9 + 7;
        static const int64_t INF = numeric_limits<int64_t>::max();

        sort(begin(packages), end(packages));
        int64_t result = INF;
        for (auto& box : boxes) {
            sort(begin(box), end(box));
            if (box.back() < packages.back()) {
                continue;
            }
            int64_t curr = 0;
            auto left = cbegin(packages);
            for (const auto& b : box) {
                auto right = upper_bound(left, cend(packages), b);
                curr += b * (right - left);
                left = right;
            }
            result = min(result, curr);
        }
        int64_t total = accumulate(cbegin(packages), cend(packages), 0LL);
        return result != INF ? (result - total) % MOD : -1;
    }


