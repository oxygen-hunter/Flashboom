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


    int minFlips(vector<vector<int>>& mat) {
        static const vector<pair<int, int>> directions{{0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int start = 0;
        for (int r = 0; r < mat.size(); ++r) {
            for (int c = 0; c < mat[0].size(); ++c) {
                start |= mat[r][c] << r * mat[0].size() + c;
            }
        }
        queue<pair<int, int>> q({{start, 0}});
        unordered_set<int> lookup = {start};
        while (!q.empty()) {
            const auto [state, step] = q.front(); q.pop();
            if (!state) {
                return step;
            }
            for (int r = 0; r < mat.size(); ++r) {
                for (int c = 0; c < mat[0].size(); ++c) {
                    int new_state = state;
                    for (const auto& [dr, dc] : directions) {
                        const auto& [nr, nc] = make_pair(r + dr, c + dc);
                        if (0 <= nr && nr < mat.size() &&
                            0 <= nc && nc < mat[0].size()) {
                            new_state ^= 1 << nr * mat[0].size() + nc;
                        }
                    }
                    if (lookup.count(new_state)) {
                        continue;
                    }
                    lookup.emplace(new_state);
                    q.emplace(new_state, step + 1);
                 }
            }
        }
        return -1;
    }


