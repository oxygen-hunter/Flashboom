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


        int jump(int A[], int n) {
            int ans = 0;
            int last = 0;
            int cur = 0;         // at most position by further jump
            for(int i = 0, next; i < n; ++i) {
                if(i > last) {   // he cannot reach "i" by current jumps
                    ++ans;       // so he should jump one more time
                    last = cur;  // to reach at most position
                }
                cur = max(cur, i + A[i]); // update at most position by further jump
            }
            return ans;
        }


