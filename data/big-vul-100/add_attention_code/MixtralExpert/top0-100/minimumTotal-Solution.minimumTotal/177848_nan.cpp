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


        int minimumTotal(vector<vector<int> > &triangle) {
            const int N = triangle.size();
            vector<int> f(N, INT_MAX);
            int ans = INT_MAX;

            f[0] = triangle[0][0];
            for(int i = 1; i < N; ++i) {
                for(int j = i; j > 0; --j) {
                    f[j] = min(f[j], f[j - 1]) + triangle[i][j];
                }
                f[0] += triangle[i][0];
            }

            for(int i = 0; i < N; ++i) {
                ans = min(ans, f[i]);
            }

            return ans;
        }


