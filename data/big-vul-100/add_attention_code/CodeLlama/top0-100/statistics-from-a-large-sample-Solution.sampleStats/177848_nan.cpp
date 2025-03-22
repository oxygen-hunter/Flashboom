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


    vector<double> sampleStats(vector<int>& count) {
        const double mi = distance(count.cbegin(), find_if(count.cbegin(), count.cend(), 
                                   [](int x) { return x != 0; }));
        
        const double ma = count.size() - 1 - 
                          distance(count.crbegin(), find_if(count.crbegin(), count.crend(), 
                                   [](int x) { return x != 0; }));
        
        const auto& n = accumulate(count.cbegin(), count.cend(), 0);
        double total = 0.0;
        for (int i = 0; i < count.size(); ++i) {
            total += double(i) * count[i];
        }
        const double mean = total / n;
        
        const double mode = distance(count.cbegin(), max_element(count.cbegin(), count.cend()));
        
        for (int i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }
        const auto& median1 = distance(count.cbegin(), lower_bound(count.cbegin(), count.cend(), (n + 1) / 2));
        const auto& median2 = distance(count.cbegin(), lower_bound(count.cbegin(), count.cend(), (n + 2) / 2));
        const double median = (median1 + median2) / 2.0;
        
        return {mi, ma, mean, median, mode};
    }


