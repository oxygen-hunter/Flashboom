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


    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        const auto n = nums.size();
        vector<int> accu = {0};
        for (const auto& num : nums) {
            accu.emplace_back(accu.back() + num);
        }
       
        vector<int> left_pos(n);
        for (int i = k, total = accu[k] - accu[0]; i < n; ++i) {
            if (accu[i + 1] - accu[i + 1 - k] > total) {
                left_pos[i] = i + 1 - k;
                total = accu[i + 1] - accu[i + 1 - k];
            } else { 
                left_pos[i] = left_pos[i - 1];
            }
        }
        
        vector<int> right_pos(n, n - k);
        for (int i = n - k - 1, total = accu[n] - accu[n - k]; i >= 0; --i) {
            if (accu[i + k] - accu[i] > total) {
                right_pos[i] = i;
                total = accu[i + k] - accu[i];
            } else {
                right_pos[i] = right_pos[i + 1];
            }
        }
        
        vector<int> result(3);
        for (int i = k, max_sum = 0; i <= n - 2 * k; ++i) {
            auto left = left_pos[i - 1], right = right_pos[i + k];
            auto total = (accu[i + k] - accu[i]) +
                         (accu[left + k] - accu[left]) +
                         (accu[right + k] - accu[right]);
            if (total > max_sum) {
                max_sum = total;
                result = {left, i, right};
            }
        }
        return result;
    }


