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

    int minKnightMoves(int x, int y) {
        // we can observe from:
        // [0]
        // [3, 2]
        // [2,(1),4]
        // [3, 2, 3, 2]
        // [2, 3,(2) 3, 4]
        // [3, 4, 3, 4, 3, 4]
        // [4, 3, 4,(3),4, 5, 4]
        // [5, 4, 5, 4, 5, 4, 5, 6]
        // [4, 5, 4, 5,(4),5, 6, 5, 6]
        // [5, 6, 5, 6, 5, 6, 5, 6, 7, 6]
        // [6, 5, 6, 5, 6,(5),6, 7, 6, 7, 8]
        // [7, 6, 7, 6, 7, 6, 7, 6, 7, 8, 7, 8]
        // [6, 7, 6, 7, 6, 7,(6),7, 8, 7, 8, 9, 8]
        // [7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 9, 8, 9, 10]
        // [8, 7, 8, 7, 8, 7, 8,(7),8, 9, 8, 9, 10, 9, 10]
        // [9, 8, 9, 8, 9, 8, 9, 8, 9, 8, 9, 10, 9, 10, 11, 10]

        x = abs(x), y = abs(y);
        if (x < y) {
            swap(x, y);
        }
        static const unordered_map<pair<int, int>, int, PairHash<int>> lookup =
            {{{1, 0}, 3}, {{2, 2}, 4}};  // special cases
        if (lookup.count({x, y})) {
            return lookup.at({x, y});
        }
        const auto& k = x - y;
        if (y > k) {
            // if 2y > x, every period 3 of y (or k) with fixed another is increased by 2 (or 1)
            // and start from (2k, k) with (k) when y = k (diagonal line)
            // ex. (0, 0) ~ (12, 12) ~ ... : 0 => 2,4(special case),2 => 4,4,4 => 6,6,6 => 8,8,8 => ...
            // ex. (2, 1) ~ (14, 13) ~ ... : 1 => 3,3,3 => 5,5,5 => 7,7,7 => 9,9,9 => ...
            return k + 2 * ((y - k - 1) / 3 + 1);
        }
        // if 2y <= x, every period 4 of k (or y) with fixed another is increased by 2
        // and start from (2k, k) with (k) when y = k (vertical line)
        // ex. (0, 0) ~ (11, 0) ~ ... : 0,3(special case),2,3 => 2,3,4,5 => 4,5,6,7 => ...
        // ex. (2, 1) ~ (13, 1) ~ ... : 1,2,3,4 => 3,4,5,6 => 5,6,7,8 => ...
        return k - 2 * ((k - y) / 4);
    }

