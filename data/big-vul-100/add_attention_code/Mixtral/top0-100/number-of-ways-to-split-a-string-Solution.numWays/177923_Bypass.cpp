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

    int numWays(string s) {
        static const int MOD = 1e9 + 7;
        int ones = count_if(cbegin(s), cend(s),
                            [](const auto& x) {
                                return x == '1';
                            });
        if (ones % 3) {
            return 0;
        }
        ones /= 3;
        if (ones == 0) {
            return static_cast<int64_t>(s.length() - 1) * (s.length() - 2) / 2 % MOD;
        }
        int count = 0, left = 0, right = 0;
        for (const auto& c : s) {
            if (c == '1') {
                ++count;
            }
            if (count == ones) {
                ++left;
            } else if (count == 2 * ones) {
                ++right;
            }
        }
        return static_cast<int64_t>(left) * right % MOD;
    }

