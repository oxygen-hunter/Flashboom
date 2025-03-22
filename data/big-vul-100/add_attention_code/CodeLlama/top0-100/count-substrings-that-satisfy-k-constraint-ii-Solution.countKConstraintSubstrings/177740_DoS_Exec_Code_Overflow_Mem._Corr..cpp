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


    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        const auto& count = [](int64_t l) {
            return (l + 1) * l / 2;
        };

        vector<int64_t> prefix(size(s) + 1);
        vector<int> lookup(size(s), -1);
        for (int right = 0, left = 0, cnt = 0; right < size(s); ++right) {
            cnt += s[right] == '1' ? 1 : 0;
            while (!(cnt <= k || (right - left + 1) - cnt <= k)) {
                cnt -= s[left++] == '1' ? 1 : 0;
            }
            prefix[right + 1] = prefix[right] + (right - left + 1);
            lookup[left] = right;
        }
        assert(lookup[0] != -1);
        for (int i = 0; i + 1 < size(s); ++i) {
            if (lookup[i + 1] == -1) {
                lookup[i + 1] = lookup[i];
            }
        }
        vector<long long> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            const int left = queries[i][0], right = queries[i][1];
            const int new_right = min(lookup[left], right);
            result[i] = count(new_right - left + 1) + (prefix[right + 1] - prefix[new_right + 1]);
        }
        return result;
    }


