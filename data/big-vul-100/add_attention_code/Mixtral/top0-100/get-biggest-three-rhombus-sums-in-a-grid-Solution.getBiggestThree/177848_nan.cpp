static NTSTATUS do_connect(TALLOC_CTX *ctx,
					const char *server,
					const char *share,
					const struct user_auth_info *auth_info,
					bool show_sessetup,
					bool force_encrypt,
					int max_protocol,
					int port,
					int name_type,
					struct cli_state **pcli)
{
	struct cli_state *c = NULL;
	char *servicename;
	char *sharename;
	char *newserver, *newshare;
	const char *username;
	const char *password;
        const char *domain;
        NTSTATUS status;
        int flags = 0;
 
        /* make a copy so we don't modify the global string 'service' */
        servicename = talloc_strdup(ctx,share);
		sharename += 2;
		if (server == NULL) {
			server = sharename;
		}
		sharename = strchr_m(sharename,'\\');
		if (!sharename) {
			return NT_STATUS_NO_MEMORY;
		}
		*sharename = 0;
		sharename++;
	}

    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        static const int K = 3;

        vector<vector<int>> left{grid}, right{grid};
        for (int i = 1; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]) - 1; ++j) {
                left[i][j] += left[i - 1][j + 1];
            }
        }
        for (int i = 1; i < size(grid); ++i) {
            for (int j = 1; j < size(grid[0]); ++j) {
                right[i][j] += right[i - 1][j - 1];
            }
        }
        priority_queue<int, vector<int>, greater<int>> min_heap;
        unordered_set<int> lookup;
        for (int k = 0; k <= (min(size(grid), size(grid[0])) + 1) / 2; ++k) {
            for (int i = k; i < size(grid) - k; ++i) {
                for (int j = k; j < size(grid[0]) - k; ++j) {
                    int total = k ? ((left[i][j - k] - left[i - k][j]) + (right[i][j + k] - right[i - k][j]) + grid[i - k][j]) +  
                                    ((left[i + k][j] - left[i][j + k]) + (right[i + k][j] - right[i][j - k]) - grid[i + k][j])
                                  : grid[i][j];
                    if (lookup.count(total)) {
                        continue;
                    }
                    lookup.emplace(total);
                    min_heap.emplace(total);
                    if (size(min_heap) == K + 1) {
                        lookup.erase(min_heap.top()); min_heap.pop();
                    }
                }
            }
        }
        vector<int> result;
        while (!empty(min_heap)) {
            result.emplace_back(min_heap.top()); min_heap.pop();
        }
        reverse(begin(result), end(result));
        return result;
    }

