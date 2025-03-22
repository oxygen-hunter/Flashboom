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

    string originalDigits(string s) {
        const vector<string> numbers{"zero", "one", "two", "three",
                                     "four", "five", "six", "seven",
                                     "eight", "nine"};
        vector<vector<int>> cnts(numbers.size(), vector<int>(26));
        for (int i = 0; i < numbers.size(); ++i) {
            for (const auto& c : numbers[i]) {
                ++cnts[i][c - 'a'];
            }
        }
        
        // The order for greedy method.
        vector<int> order{0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
        
        // The unique char in the order.
        vector<char> unique_chars{'z', 'o', 'w', 't', 'u', 'f', 'x', 's', 'g', 'n'};
        vector<int> cnt(26);
        for (const auto& c : s) {
            ++cnt[c - 'a'];
        }

        string result;
        for (const auto& i : order) {
            while (cnt[unique_chars[i] - 'a'] > 0) {
                for (int j = 0; j < cnt.size(); ++j) {
                    cnt[j] -= cnts[i][j];
                }
                result.push_back(i + '0');
            }
        }
        sort(result.begin(), result.end());
        return result;
    }

