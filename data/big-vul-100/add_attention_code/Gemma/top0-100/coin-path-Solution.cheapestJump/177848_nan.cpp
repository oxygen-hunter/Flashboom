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


    vector<int> cheapestJump(vector<int>& A, int B) {
        vector<int> result;
        if (A.empty() || A.back() == -1) {
            return result;
        }
        const int n = A.size();
        vector<int> dp(n, numeric_limits<int>::max()), next(n, -1);
        dp[n - 1] = A[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            if (A[i] == -1) {
                continue;
            }
            for (int j = i + 1; j <= min(i + B, n - 1); ++j) {
                if (dp[j] == numeric_limits<int>::max()) {
                    continue;
                }
                if (A[i] + dp[j] < dp[i]) {
                    dp[i] = A[i] + dp[j];
                    next[i] = j;
                }
            }
        }
        if (dp[0] == numeric_limits<int>::max()) {
            return result;
        }
        int k = 0;
        while (k != -1) {
            result.emplace_back(k + 1);
            k = next[k];
        }
        return result;
    }


