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

    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        const auto& KMP = [](const auto& text, const auto& pattern) {
            const auto& getPrefix = [](const auto& pattern) {
                vector<int> prefix(size(pattern), -1);
                int j = -1;
                for (int i = 1; i < size(pattern); ++i) {
                    while (j != -1 && pattern[j + 1] != pattern[i]) {
                        j = prefix[j];
                    }
                    if (pattern[j + 1] == pattern[i]) {
                        ++j;
                    }
                    prefix[i] = j;
                }
                return prefix;
            };

            int result = 0;
            const vector<int> prefix = getPrefix(pattern);
            int j = -1;
            for (int i = 0; i < size(text); ++i) {
                while (j > -1 && pattern[j + 1] != text[i]) {
                    j = prefix[j];
                }
                if (pattern[j + 1] == text[i]) {
                    ++j;
                }
                if (j == size(pattern) - 1) {
                    ++result;
                    j = prefix[j];
                }
            }
            return result;
        };
    
        for (int i = 0; i + 1 < size(nums); ++i) {
            if (nums[i + 1] > nums[i]) {
                nums[i] = 1;
            } else if (nums[i + 1] < nums[i]) {
                nums[i] = -1;
            } else {
                nums[i] = 0;
            }
        }
        return KMP(nums, pattern);
    }

