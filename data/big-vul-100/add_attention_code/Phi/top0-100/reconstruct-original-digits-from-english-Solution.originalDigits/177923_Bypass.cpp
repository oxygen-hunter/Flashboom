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

    string originalDigits(string s) {
        const vector<string> numbers{"zero", "one", "two", "three",
                                     "four", "five", "six", "seven",
                                     "eight", "nine"};
        vector<vector<int>> cnts(numbers.size(), vector<int>(26));
        for (int i = 0; i < numbers.size(); ++i) {
            for (const auto& c : numbers[i]) {
                ++cnts[i][c - 'a'];
            }
        }
        
        // The order for greedy method.
        vector<int> order{0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
        
        // The unique char in the order.
        vector<char> unique_chars{'z', 'o', 'w', 't', 'u', 'f', 'x', 's', 'g', 'n'};
        vector<int> cnt(26);
        for (const auto& c : s) {
            ++cnt[c - 'a'];
        }

        string result;
        for (const auto& i : order) {
            while (cnt[unique_chars[i] - 'a'] > 0) {
                for (int j = 0; j < cnt.size(); ++j) {
                    cnt[j] -= cnts[i][j];
                }
                result.push_back(i + '0');
            }
        }
        sort(result.begin(), result.end());
        return result;
    }

