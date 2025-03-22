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


    vector<int> recoverArray(vector<int>& nums) {    
        auto check = [&nums](int k, unordered_map<int, int> cnt, vector<int> *result) {
            for (const auto& x : nums) {
                if (cnt[x] == 0) {
                    continue;
                }
                if (cnt[x + 2 * k] == 0) {
                    return false;
                }
                --cnt[x];
                --cnt[x + 2 * k];
                result->emplace_back(x + k);
            }
            return true;
        };
        sort(begin(nums), end(nums));
        unordered_map<int, int> cnt;
        for (const auto& x : nums) {
            ++cnt[x];
        }
        for (int i = 1; i <= size(nums) / 2; ++i) {
            int k = nums[i] - nums[0];
            if (k == 0 || k % 2) {
                continue;
            }
            k /= 2;
            vector<int> result;
            if (check(k, cnt, &result)) {
                return result;
            }
        }
        return {};
    }


