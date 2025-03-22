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

    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        using ordered_set = tree<pair<int, int64_t>, null_type, greater<pair<int, int64_t>>, rb_tree_tag, tree_order_statistics_node_update>;
        ordered_set os;
        unordered_map<int, int64_t> cnt;
        const auto& update = [&](int v, int64_t d, int64_t curr) {
            if (d == 1) {
                os.insert({cnt[v], v});
            }
            if (os.order_of_key(pair(cnt[v], v)) < x) {
                curr += d * cnt[v] * v;
                if (x < size(os)) {
                    const auto [nc, nv] = *(os.find_by_order(x));
                    curr -= d * nc * nv;
                }
            }
            if (d != 1) {
                os.erase(pair(cnt[v], v));
            }
            return curr;
        };

        vector<long long> result;
        for (int64_t i = 0, curr = 0; i < size(nums); ++i) {
            if (cnt.count(nums[i])) {
                curr = update(nums[i], -1, curr);
            }
            ++cnt[nums[i]];
            curr = update(nums[i], +1, curr);
            if (i < k - 1) {
                continue;
            }
            result.emplace_back(curr);
            curr = update(nums[i - (k - 1)], -1, curr);
            --cnt[nums[i - (k - 1)]];
            if (cnt[nums[i - (k - 1)]]) {
                curr = update(nums[i - (k - 1)], +1, curr);
            } else {
                cnt.erase(nums[i - (k - 1)]);
            }
        }
        return result;
    }

