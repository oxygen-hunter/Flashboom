static php_stream *phar_make_dirstream(char *dir, HashTable *manifest TSRMLS_DC) /* {{{ */
{
	HashTable *data;
	int dirlen = strlen(dir);
	phar_zstr key;
	char *entry, *found, *save, *str_key;
	uint keylen;
	ulong unused;

	ALLOC_HASHTABLE(data);
	zend_hash_init(data, 64, zend_get_hash_value, NULL, 0);

	if ((*dir == '/' && dirlen == 1 && (manifest->nNumOfElements == 0)) || (dirlen >= sizeof(".phar")-1 && !memcmp(dir, ".phar", sizeof(".phar")-1))) {
		/* make empty root directory for empty phar */
		/* make empty directory for .phar magic directory */
		efree(dir);
		return php_stream_alloc(&phar_dir_ops, data, NULL, "r");
	}

        zend_hash_internal_pointer_reset(manifest);
 
        while (FAILURE != zend_hash_has_more_elements(manifest)) {
               if (HASH_KEY_IS_STRING != zend_hash_get_current_key_ex(manifest, &key, &keylen, &unused, 0, NULL)) {
                        break;
                }
 
		PHAR_STR(key, str_key);

		if (keylen <= (uint)dirlen) {
			if (keylen < (uint)dirlen || !strncmp(str_key, dir, dirlen)) {
				PHAR_STR_FREE(str_key);
				if (SUCCESS != zend_hash_move_forward(manifest)) {
					break;
				}
				continue;
			}
		}

		if (*dir == '/') {
			/* root directory */
			if (keylen >= sizeof(".phar")-1 && !memcmp(str_key, ".phar", sizeof(".phar")-1)) {
				PHAR_STR_FREE(str_key);
				/* do not add any magic entries to this directory */
				if (SUCCESS != zend_hash_move_forward(manifest)) {
					break;
				}
				continue;
			}

			if (NULL != (found = (char *) memchr(str_key, '/', keylen))) {
				/* the entry has a path separator and is a subdirectory */
				entry = (char *) safe_emalloc(found - str_key, 1, 1);
				memcpy(entry, str_key, found - str_key);
				keylen = found - str_key;
				entry[keylen] = '\0';
			} else {
				entry = (char *) safe_emalloc(keylen, 1, 1);
				memcpy(entry, str_key, keylen);
				entry[keylen] = '\0';
			}

			PHAR_STR_FREE(str_key);
			goto PHAR_ADD_ENTRY;
		} else {
			if (0 != memcmp(str_key, dir, dirlen)) {
				/* entry in directory not found */
				PHAR_STR_FREE(str_key);
				if (SUCCESS != zend_hash_move_forward(manifest)) {
					break;
				}
				continue;
			} else {
				if (str_key[dirlen] != '/') {
					PHAR_STR_FREE(str_key);
					if (SUCCESS != zend_hash_move_forward(manifest)) {
						break;
					}
					continue;
				}
			}
		}

		save = str_key;
		save += dirlen + 1; /* seek to just past the path separator */

		if (NULL != (found = (char *) memchr(save, '/', keylen - dirlen - 1))) {
			/* is subdirectory */
			save -= dirlen + 1;
			entry = (char *) safe_emalloc(found - save + dirlen, 1, 1);
			memcpy(entry, save + dirlen + 1, found - save - dirlen - 1);
			keylen = found - save - dirlen - 1;
			entry[keylen] = '\0';
		} else {
			/* is file */
			save -= dirlen + 1;
			entry = (char *) safe_emalloc(keylen - dirlen, 1, 1);
			memcpy(entry, save + dirlen + 1, keylen - dirlen - 1);
			entry[keylen - dirlen - 1] = '\0';
			keylen = keylen - dirlen - 1;
		}
		PHAR_STR_FREE(str_key);
PHAR_ADD_ENTRY:
		if (keylen) {
			phar_add_empty(data, entry, keylen);
		}

		efree(entry);

		if (SUCCESS != zend_hash_move_forward(manifest)) {
			break;
		}
	}

	if (FAILURE != zend_hash_has_more_elements(data)) {
		efree(dir);
		if (zend_hash_sort(data, zend_qsort, phar_compare_dir_name, 0 TSRMLS_CC) == FAILURE) {
			FREE_HASHTABLE(data);
			return NULL;
		}
		return php_stream_alloc(&phar_dir_ops, data, NULL, "r");
	} else {
		efree(dir);
		return php_stream_alloc(&phar_dir_ops, data, NULL, "r");
	}
}
/* }}}*/

    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        static const double EPS = 1e-15;
        static const int MOD = 1e9 + 7;
        const auto& powmod = [&](int a, int b) {
            a %= MOD;
            int64_t result = 1;
            while (b) {
                if (b & 1) {
                    result = result * a % MOD;
                }
                a = int64_t(a) * a % MOD;
                b >>= 1;
            }
            return result;
        };

        const auto& binary_search_right = [](auto left, auto right, const auto& check) {
            while (left <= right) {
                const auto mid = left + (right - left) / 2;
                if (!check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return right;
        };

        const auto& count = [](const auto& x, int target) {
            return static_cast<int>(target - x + EPS);
        };

        if (multiplier == 1) {
            return nums;
        }
        using P = pair<double, int>;
        vector<P> vals;
        for (int i = 0; i < size(nums); ++i) {
            vals.emplace_back(log(nums[i]) / log(multiplier), i);
        }
        sort(begin(vals), end(vals));
        const auto& check = [&](const auto& target) {
            int result = 0;
            for (const auto& [x, i] : vals) {
                const int c = count(x, target);
                if (c <= 0) {
                    break;
                }
                result += c;
            }
            return result <= k;
        };

        const int target = binary_search_right(1, static_cast<int>(vals.back().first) + 1, check);
        vector<int64_t> nums2(cbegin(nums), cend(nums));
        for (int idx = 0; idx < size(vals); ++idx) {
            const auto& [x, i] = vals[idx];
            const int c = count(x, target);
            if (c <= 0) {
                break;
            }
            k -= c;
            nums2[i] *= pow(multiplier, c);
        }
        using P2 = pair<int64_t, int>;
        vector<P2> vals2;
        for (int i = 0; i < size(nums2); ++i) {
            vals2.emplace_back(nums2[i], i);
        }
        sort(begin(vals2), end(vals2));
        const int q = k / size(nums), r = k % size(nums);
        const int m = powmod(multiplier, q);
        vector<int> result(size(nums));
        for (int idx = 0; idx < size(vals2); ++idx) {
            const auto& [x, i] = vals2[idx];
            result[i] = ((x % MOD * m) % MOD * (idx < r ? multiplier : 1)) % MOD;
        }
        return result;
    }

