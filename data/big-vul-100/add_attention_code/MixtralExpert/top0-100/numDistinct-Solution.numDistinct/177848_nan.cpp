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


        int numDistinct(const string &S, const string &T) {
            vector<int> f(T.size() + 1);
            f[0] = 1; // f(0, 0) = 1, means S = "" and T = "", there is only one distinct subsequence, i.e. ""
            for (int i = 1; i <= S.size(); ++i) {
                for (int j = T.size(); j > 0; --j) {
                    // f(i, j) is composed of:
                    // f(i−1,j): not using S[i - 1] 
                    // f(i−1,j−1): using S[i - 1] if S[i - 1] == S[j - 1]
                    f[j] += (S[i - 1] == T[j - 1]) ? f[j - 1] : 0;
                }
            }
            return f[T.size()];
        }


