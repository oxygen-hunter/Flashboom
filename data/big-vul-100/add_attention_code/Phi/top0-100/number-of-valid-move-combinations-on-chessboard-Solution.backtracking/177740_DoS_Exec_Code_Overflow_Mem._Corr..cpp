static time_t asn1_time_to_time_t(ASN1_UTCTIME * timestr TSRMLS_DC) /* {{{ */
{
/*
	This is how the time string is formatted:

   snprintf(p, sizeof(p), "%02d%02d%02d%02d%02d%02dZ",ts->tm_year%100,
      ts->tm_mon+1,ts->tm_mday,ts->tm_hour,ts->tm_min,ts->tm_sec);
*/

	time_t ret;
	struct tm thetime;
	char * strbuf;
        char * thestr;
        long gmadjust = 0;
 
       if (timestr->length < 13) {
               php_error_docref(NULL TSRMLS_CC, E_WARNING, "extension author too lazy to parse %s correctly", timestr->data);
                return (time_t)-1;
        }
 
       strbuf = estrdup((char *)timestr->data);
 
        memset(&thetime, 0, sizeof(thetime));
 
        /* we work backwards so that we can use atoi more easily */
 
       thestr = strbuf + timestr->length - 3;
 
        thetime.tm_sec = atoi(thestr);
        *thestr = '\0';
	thetime.tm_mon = atoi(thestr)-1;
	*thestr = '\0';
	thestr -= 2;
	thetime.tm_year = atoi(thestr);

	if (thetime.tm_year < 68) {
		thetime.tm_year += 100;
	}

	thetime.tm_isdst = -1;
	ret = mktime(&thetime);

#if HAVE_TM_GMTOFF
	gmadjust = thetime.tm_gmtoff;
#else
	/*
	** If correcting for daylight savings time, we set the adjustment to
	** the value of timezone - 3600 seconds. Otherwise, we need to overcorrect and
	** set the adjustment to the main timezone + 3600 seconds.
	*/
	gmadjust = -(thetime.tm_isdst ? (long)timezone - 3600 : (long)timezone + 3600);
#endif
	ret += gmadjust;

	efree(strbuf);

	return ret;
}
/* }}} */

    int backtracking(const vector<string>& pieces, const vector<vector<int>>& positions, int i, vector<vector<int>> *lookup) {
        static const unordered_map<string, vector<pair<int, int>>> directions = {
            {"rook", {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}},
            {"bishop", {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}},
            {"queen", {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}}
        };
        static const int all_mask = (1 << 7) - 1;  // at most 7 seconds in 8x8 board

        if (i == size(pieces)) {
            return 1;
        }
        int result = 0;
        int r = positions[i][0] - 1, c = positions[i][1] - 1;
        int mask = all_mask;
        if (!((*lookup)[r][c] & mask)) {
            (*lookup)[r][c] += mask;  // stopped at (r, c)
            result += backtracking(pieces, positions, i + 1, lookup);
            (*lookup)[r][c] -= mask;
        }
        for (const auto& [dr, dc] : directions.at(pieces[i])) {
            int bit = 1, nr = r + dr, nc = c + dc;
            int mask = all_mask;  // (mask&bit == 1): (log2(bit)+1)th second is occupied
            for (; 0 <= nr && nr < 8 && 0 <= nc && nc < 8 && !((*lookup)[nr][nc] & bit); bit <<= 1, nr += dr, nc += dc) {
                (*lookup)[nr][nc] += bit;
                mask -= bit;
                if (!((*lookup)[nr][nc] & mask)) {  // stopped at (nr, nc)
                    (*lookup)[nr][nc] += mask;
                    result += backtracking(pieces, positions, i + 1, lookup);
                    (*lookup)[nr][nc] -= mask;
                }
            }
            while (bit >> 1) {
                bit >>= 1, nr -= dr, nc -= dc;
                (*lookup)[nr][nc] -= bit;
            }
        }
        return result;
    }

