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


    int dieSimulator(int n, vector<int>& rollMax) {
        static const int MOD = 1e9 + 7;
        vector<vector<int>> dp;
        for (int i = 0; i < 6; ++i) {
            dp.emplace_back(rollMax[i]);
            dp[i][0] = 1;  // 0-indexed
        }
        while (--n) {
            vector<vector<int>> new_dp;
            for (int i = 0; i < 6; ++i) {
                new_dp.emplace_back(rollMax[i]);  
            }
            for (int i = 0; i < 6; ++i) {
                for (int k = 0; k < rollMax[i]; ++k) {
                    for (int j = 0; j < 6; ++j) {
                        if (i == j) {
                            if (k < rollMax[i] - 1) {  // 0-indexed
                                new_dp[j][k + 1] = (new_dp[j][k + 1] + dp[i][k]) % MOD;
                            }
                        } else {
                            new_dp[j][0] = (new_dp[j][0] + dp[i][k]) % MOD;
                        }
                    }
                }
            }
            dp = move(new_dp);
        }
        uint64_t result = 0;
        for (const auto& row : dp) {
            const auto& total =
                accumulate(row.cbegin(), row.cend(),
                           0ull,
                           [&](const auto& a, const auto& b) {
                               return (a + b) % MOD;
                           });
            result = (result + total) % MOD;
        }
        return result;
    }


