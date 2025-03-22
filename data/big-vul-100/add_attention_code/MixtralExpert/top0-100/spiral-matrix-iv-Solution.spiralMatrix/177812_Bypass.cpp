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


    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        static const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        vector<vector<int>> result(m, vector<int>(n, -1));
        for (int i = 0, j = 0, d = 0; head; head = head->next) {
            result[i][j] = head->val;
            if (!(0 <= i + directions[d].first && i + directions[d].first < m &&
                  0 <= j + directions[d].second && j + directions[d].second < n &&
                  result[i + directions[d].first][j + directions[d].second] == -1)) {
                d = (d + 1) % 4;
            }
            i += directions[d].first;
            j += directions[d].second;
        }
        return result;
    }


