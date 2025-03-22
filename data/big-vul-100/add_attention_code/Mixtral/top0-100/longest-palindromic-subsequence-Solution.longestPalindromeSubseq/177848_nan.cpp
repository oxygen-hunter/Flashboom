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

    int longestPalindromeSubseq(string s) {
        if (s == string(s.rbegin(), s.rend())) {  // optional, to optimize special case
            return s.length();
        }
        
        vector<vector<int>> dp(2, vector<int>(s.size(), 1));
        for (int i = s.length() - 2; i >= 0; --i) {
            for (int j = i + 1; j < s.length(); ++j) {
                if (s[i] == s[j]) {
                    dp[i % 2][j] = (i + 1 <= j - 1) ? 2 + dp[(i + 1) % 2][j - 1] : 2;
                } else {
                    dp[i % 2][j] = max(dp[(i + 1) % 2][j], dp[i % 2][j - 1]);
                }
            }
        }
        return dp[0][s.length() - 1];
    }

