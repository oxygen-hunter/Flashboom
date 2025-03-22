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


    int maxProductPath(vector<vector<int>>& grid) {
        static const int MOD = 1e9 + 7;
        vector<vector<int64_t>> max_dp(2, vector<int64_t>(size(grid[0])));
        vector<vector<int64_t>> min_dp(2, vector<int64_t>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                if (i == 0 && j == 0) {
                    max_dp[0][0] = min_dp[0][0] = grid[0][0];
                    continue;
                }
                auto curr_max = max(i > 0 ? max_dp[(i - 1) % 2][j] : max_dp[i % 2][j - 1],
                                    j > 0 ? max_dp[i % 2][j - 1] : max_dp[(i - 1) % 2][j]);
                auto curr_min = min(i > 0 ? min_dp[(i - 1) % 2][j] : min_dp[i % 2][j - 1],
                                    j > 0 ? min_dp[i % 2][j - 1] : min_dp[(i - 1) % 2][j]);
                if (grid[i][j] < 0) {
                    swap(curr_max, curr_min);
                }
                max_dp[i % 2][j] = curr_max * grid[i][j];
                min_dp[i % 2][j] = curr_min * grid[i][j];
            }
        }
        return max_dp[(size(grid) - 1) % 2].back() >= 0 ? max_dp[(size(grid) - 1) % 2].back() % MOD : -1;
    }


