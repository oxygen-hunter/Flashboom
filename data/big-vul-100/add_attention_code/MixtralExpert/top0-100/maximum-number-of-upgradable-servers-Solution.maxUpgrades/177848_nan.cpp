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


    vector<int> maxUpgrades(vector<int>& count, vector<int>& upgrade, vector<int>& sell, vector<int>& money) {
        const auto& ceil_divide = [](const auto& a, const auto& b) {
            return (a + b - 1) / b ;
        };

        // let x be the number of sold servers
        // (c-x)*u <= m+(x*s)
        // x >= (c*u-m)//(u+s) <= 0
        // c-x <= c-(c*u-m)//(u+s) <= c
        vector<int> result(size(count));
        for (int i = 0; i < size(count); ++i) {
            result[i] = min(count[i] - ceil_divide(static_cast<int64_t>(count[i]) * upgrade[i] - money[i], upgrade[i] + sell[i]), static_cast<int64_t>(count[i]));
        }
        return result;
    }


