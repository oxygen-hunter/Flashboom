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


    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        const auto& binary_search = [](auto left, auto right, const auto& check) {
            while (left <= right) {
                const auto mid = left + ((right - left) / 2);
                if (check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };

        const auto& powmod = [&](auto a, auto b, int mod) {
            a %= mod;
            auto result = 1 % mod;
            while (b) {
                if (b & 1) {
                    result = result * a % mod;
                }
                a = a * a % mod;
                b >>= 1;
            }
            return result;
        };

        const auto& count1 = [&](auto x) {
            auto result = 0ll;
            for (int i = 0; (1ll << i) <= x; ++i) {
                const auto mask = (1ll << (i + 1)) - 1;
                result += ((x & ~mask) >> 1) + max((x & mask) - (1ll << i) + 1, 0ll);
            }
            return result;
        };
        
        const auto& count2 = [&](auto x) {
            auto result = 0ll;
            for (int i = 0; (1ll << i) <= x; ++i) {
                const auto mask = (1ll << (i + 1)) - 1;
                result += (((x & ~mask) >> 1) + max((x & mask) - (1ll << i) + 1, 0ll)) * i;
            }
            return result;
        };
    
        const auto& f = [&](auto x) {
            const auto y = binary_search(1ll, x - 1, [&](auto i) {
                return count1(i) >= x;
            });
            auto result = count2(y - 1);
            x -= count1(y - 1);
            for (int i = 0; (1ll << i) <= y; ++i) {
                if ((y & (1ll << i)) == 0) {
                    continue;
                }
                result += i;
                if (--x == 0) {
                    break;
                }
            }
            return result;
        };
    
        vector<int> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            const auto left = queries[i][0], right = queries[i][1], mod = queries[i][2];
            result[i] =  powmod(2ll, f(right + 1) - f(left), mod);
        }
        return result;
    }


