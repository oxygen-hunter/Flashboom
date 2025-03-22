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

    int totalStrength(vector<int>& strength) {
        static const int MOD = 1e9 + 7;
        const auto& add = [&](const int64_t a, const int64_t b) {
            return (a + b) % MOD;
        };
        const auto& sub = [&](const int64_t a, const int64_t b) {
            return (a - b + MOD) % MOD;
        };
        const auto& mult = [&](const int64_t a, const int64_t b) {
            return (a * b) % MOD;
        };
        vector<int64_t> prefix(size(strength) + 1), prefix2(size(strength) + 1);
        for (int i = 0; i < size(strength); ++i) {
            prefix[i + 1] = add(prefix[i], strength[i]);
            prefix2[i + 1] = add(prefix2[i], strength[i] * static_cast<int64_t>(i + 1));
        }
        vector<int64_t> suffix(size(strength) + 1), suffix2(size(strength) + 1);
        for (int i = size(strength) - 1; i >= 0; --i) {
            suffix[i] = add(suffix[i + 1], strength[i]);
            suffix2[i] = add(suffix2[i + 1], strength[i] * (size(strength) - i));
        }
        vector<int> stk = {-1};
        int result = 0;
        for (int i = 0; i <= size(strength); ++i) {
            while (stk.back() != -1 && (i == size(strength) || strength[stk.back()] >= strength[i])) {
                const int x = stk[size(stk) - 2] + 1;
                const int y = stk.back(); stk.pop_back();
                const int z = i - 1;
                // assert(all(strength[j] >= strength[y] for j in xrange(x, y+1)))
                // assert(all(strength[j] > strength[y] for j in xrange(y+1, z+1)))
                const int64_t left = mult(z - y + 1, sub(sub(prefix2[y + 1], prefix2[x]), mult(x, sub(prefix[y + 1], prefix[x]))));
                const int64_t right = mult(y - x + 1, sub(sub(suffix2[y + 1], suffix2[z + 1]), mult(size(strength) - (z + 1), sub(suffix[y + 1], suffix[z + 1]))));
                result = add(result, mult(strength[y], add(left, right)));
            }
            stk.emplace_back(i);
        }
        return result;
    }

