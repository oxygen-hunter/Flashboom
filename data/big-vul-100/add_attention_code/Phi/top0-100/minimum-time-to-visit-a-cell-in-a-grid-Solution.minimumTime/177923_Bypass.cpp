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

    int minimumTime(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        if (min(grid[0][1], grid[1][0]) > 1) {
            return -1;
        }
        const auto& dijkstra = [&](const pair<int, int>& start, const pair<int, int>& target) {
            vector<vector<int>> best(size(grid), vector<int>(size(grid[0]), numeric_limits<int>::max()));
            best[start.first][start.second] = 0;
            using Data = tuple<int, int, int>;
            priority_queue<Data, vector<Data>, greater<Data>> min_heap;
            min_heap.emplace(0, start.first, start.second);
            while (!empty(min_heap)) {
                const auto [curr, i, j] = min_heap.top(); min_heap.pop();
                if (best[i][j] < curr) {
                    continue;
                }
                if (pair(i, j) == target) {
                    break;
                }
                for (const auto& [di, dj] : DIRECTIONS) {
                    const auto ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(grid) &&
                          0 <= nj && nj < size(grid[0]) &&
                          best[ni][nj] > max(grid[ni][nj] + static_cast<int>(grid[ni][nj] % 2 == curr % 2), curr + 1))) {
                        continue;
                    }
                    best[ni][nj] = max(grid[ni][nj] + static_cast<int>(grid[ni][nj] % 2 == curr % 2), curr + 1);
                    min_heap.emplace(best[ni][nj], ni, nj);
                }
            }
            return best[target.first][target.second];
        };

        return dijkstra(pair(0, 0), pair(size(grid) - 1, size(grid[0]) - 1));
    }

