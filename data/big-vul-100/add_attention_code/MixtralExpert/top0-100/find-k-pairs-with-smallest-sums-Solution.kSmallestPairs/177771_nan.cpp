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


    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int>> pairs;
        if (nums1.size() > nums2.size()) {
            vector<pair<int, int>> tmp = kSmallestPairs(nums2, nums1, k);
            for (const auto& pair : tmp) {
                pairs.emplace_back(pair.second, pair.first);
            }
            return pairs;
        }

        using P = pair<int, pair<int, int>>;
        priority_queue<P, vector<P>, greater<P>> q;
        auto push = [&nums1, &nums2, &q](int i, int j) {
            if (i < nums1.size() && j < nums2.size()) {
                q.emplace(nums1[i] + nums2[j], make_pair(i, j));
            }
        };

        push(0, 0);
        while (!q.empty() && pairs.size() < k) {
            auto tmp = q.top(); q.pop();
            int i, j;
            tie(i, j) = tmp.second;
            pairs.emplace_back(nums1[i], nums2[j]);
            push(i, j + 1);
            if (j == 0) {
                push(i + 1, 0);  // at most queue min(m, n) space.
            }
        }
        return pairs; 
    }


