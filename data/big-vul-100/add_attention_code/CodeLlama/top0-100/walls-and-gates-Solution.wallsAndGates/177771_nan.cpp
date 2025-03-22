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


    void wallsAndGates(vector<vector<int>>& rooms) {
        const int INF = numeric_limits<int>::max();
        queue<pair<int, int>> q;
        for (int i = 0; i < rooms.size(); ++i) {
            for (int j = 0; j < rooms[0].size(); ++j) {
                if (rooms[i][j] == 0) {
                    q.emplace(i, j);
                }
            }
        }
        while (!q.empty()) {
            int i, j;
            tie(i, j) = q.front();
            q.pop();
            for (const pair<int, int>& d :
                 vector<pair<int, int>>{{i + 1, j}, {i - 1, j},
                                        {i, j + 1}, {i, j - 1}}) {
                int I, J;
                tie(I, J) = d;
                if (I >= 0 && I < rooms.size() &&
                    J >= 0 && J < rooms[0].size() &&
                    rooms[I][J] == INF) {
                    rooms[I][J] = rooms[i][j] + 1;
                    q.emplace(I, J);
                }
            }
        }
    }


