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


    bool confusingNumber(int N) {
        static const unordered_map<char, char> lookup = 
            {{'0', '0'}, {'1', '1'}, {'6', '9'},
             {'8', '8'}, {'9', '6'}};
 
        const auto& S = to_string(N);
        for (int i = 0; i < S.length(); ++i) {
            if (!lookup.count(S[i])) {
                return false;
            }
        }
        for (int i = 0; i < (S.length() + 1) / 2; ++i) {
            if (S[i] != lookup.at(S[S.length() - 1 - i])) {
                return true;
            }
        }
        return false;
    }


