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


    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {
        using P = pair<int, int>;
        unordered_map<int, vector<P>> adj;
        for (const auto& highway : highways) {
            int u, v, w;
            tie(u, v, w) = make_tuple(highway[0], highway[1], highway[2]);
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        
        unordered_map<int, unordered_map<int, int>> best;
        best[0][discounts] = 0;
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(0, 0, discounts);
        while (!empty(min_heap)) {
            auto [total, u, k] = min_heap.top(); min_heap.pop();
            if ((best.count(u) && best[u].count(k) &&  best[u][k] < total)) {
                continue;
            }
            if (u == n - 1) {
                return total;
            }
            for (const auto& [v, w] : adj[u]) {
                if (!best.count(v) ||
                    !best[v].count(k) ||
                    total + w < best[v][k]) {
                    best[v][k] = total + w;
                    min_heap.emplace(total + w, v, k);
                }
                if (k > 0 &&
                    (!best.count(v) ||
                    !best[v].count(k - 1) ||
                    total + w / 2 < best[v][k - 1])) {
                    best[v][k - 1] = total + w / 2;
                    min_heap.emplace(total + w / 2, v, k - 1);
                }
            }
        }
        return -1;
    }


