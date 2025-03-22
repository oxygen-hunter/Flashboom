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


    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        const auto& next_popcount = [](uint32_t n) {  // reference: https://massivealgorithms.blogspot.com/2014/06/hakmem-item-175.html
            const uint32_t lowest_bit = n & -n;
            const uint32_t left_bits = n + lowest_bit;
            const uint32_t changed_bits = n ^ left_bits;
            const uint32_t right_bits = (changed_bits / lowest_bit) >> 2;
            return left_bits | right_bits;
        };

        vector<uint32_t> masks(size(matrix));
        for (int r = 0; r < size(matrix); ++r) {
            uint32_t m = 0;
            for (int c = 0; c < size(matrix[0]); ++c) {
                m |= matrix[r][c] << ((size(matrix[0]) - 1) - c);
            }
            masks[r] = m;
        }
        int result = 0;
        for (uint32_t mask = (1 << numSelect) - 1; mask < 1 << size(matrix[0]); mask = next_popcount(mask)) {
            const int cnt = accumulate(cbegin(masks), cend(masks), 0, [&](const auto& total, const auto& x) {
                return total + static_cast<int>((x & mask) == x);
            });
            result = max(result, cnt);
        }
        return result;
    }


