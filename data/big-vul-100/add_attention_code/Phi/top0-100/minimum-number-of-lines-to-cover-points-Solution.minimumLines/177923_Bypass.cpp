PHP_FUNCTION(move_uploaded_file)
{
	char *path, *new_path;
	int path_len, new_path_len;
	zend_bool successful = 0;

#ifndef PHP_WIN32
	int oldmask; int ret;
#endif

	if (!SG(rfc1867_uploaded_files)) {
                RETURN_FALSE;
        }
 
       if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &path, &path_len, &new_path, &new_path_len) == FAILURE) {
                return;
        }
	if (!zend_hash_exists(SG(rfc1867_uploaded_files), path, path_len + 1)) {
		RETURN_FALSE;
	}

	if (php_check_open_basedir(new_path TSRMLS_CC)) {
		RETURN_FALSE;
	}

	if (VCWD_RENAME(path, new_path) == 0) {
		successful = 1;
#ifndef PHP_WIN32
		oldmask = umask(077);
		umask(oldmask);

		ret = VCWD_CHMOD(new_path, 0666 & ~oldmask);

		if (ret == -1) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", strerror(errno));
		}
#endif
	} else if (php_copy_file_ex(path, new_path, STREAM_DISABLE_OPEN_BASEDIR TSRMLS_CC) == SUCCESS) {
		VCWD_UNLINK(path);
		successful = 1;
	}

	if (successful) {
		zend_hash_del(SG(rfc1867_uploaded_files), path, path_len + 1);
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to move '%s' to '%s'", path, new_path);
	}

	RETURN_BOOL(successful);
}

    int minimumLines(vector<vector<int>>& points) {
        auto ceil_divide = [](int a, int b) {
            return (a + b - 1) / b;
        };
        unordered_map<tuple<int, int, int>, unordered_set<pair<int, int>, PairHash<int>>, TupleHash<int, int, int>> lookup;
        for (int i = 0; i < size(points); ++i) {
            const int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < size(points); ++j) {
                const int x2 = points[j][0], y2 = points[j][1];
                // (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
                // => (y2-y1)x - (x2-x1)y = x1(y2-y1) - y1(x2-x1)
                int a = y2 - y1;
                int b = -(x2 - x1);
                int c = x1 * (y2 - y1) - y1 * (x2 - x1);
                const int g = gcd(gcd(a, b), c);
                a /= g, b /= g, c /= g;
                lookup[{a, b, c}].emplace(x1, y1);
                lookup[{a, b, c}].emplace(x2, y2);
            }
        }
        vector<tuple<int, int, int>> lines;
        for (const auto& [l, p] : lookup) {
            if (size(p) > 2) {  // filter to improve complexity
                lines.emplace_back(l);
            }
        }
        assert(size(lines) <= size(points) / 2);  // 1 extra colinear point per 2 points
        int result = numeric_limits<int>::max();
        const int mask_upper_bound = 1 << size(lines);
        for (int mask = 0; mask < mask_upper_bound; ++mask) {
            unordered_set<pair<int, int>, PairHash<int>> covered;
            for (int i = 0, bit = 1; bit <= mask; bit <<= 1, ++i) {
                if (mask & bit) {
                    for (const auto& x : lookup[lines[i]]) {
                        covered.emplace(x);
                    }
                }
            }
            result = min(result, __builtin_popcount(mask) + ceil_divide(size(points) - size(covered), 2));
        }
        return result;
    }

