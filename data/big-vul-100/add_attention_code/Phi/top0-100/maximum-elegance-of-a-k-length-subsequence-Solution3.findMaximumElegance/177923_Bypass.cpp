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

    long long findMaximumElegance(vector<vector<int>>& items, int k) {
        sort(rbegin(items), rend(items));
        vector<bool> lookup(size(items));
        vector<int> stk;
        int64_t curr = 0, l = 0;
        for (int i = 0; i < k; ++i) {
            if (lookup[items[i][1] - 1]) {
                stk.emplace_back(items[i][0]);
            }
            curr += items[i][0];
            if (!lookup[items[i][1] - 1]) {
                lookup[items[i][1] - 1] = true;
                ++l;
            }
        }
        int64_t result = curr + l * l;
        for (int i = k; i < size(items); ++i) {
            if (lookup[items[i][1] - 1]) {
                continue;
            }
            if (empty(stk)) {
                break;
            }
            curr += items[i][0] - stk.back(); stk.pop_back();
            lookup[items[i][1] - 1] = true;
            ++l;
            result = max(result, curr + l * l);
        }
        return result;
    }

