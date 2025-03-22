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

    bool isPossible(vector<int>& target) {
        // (1) x + remain = y
        // (2) y + remain = total
        // (1) - (2) => x - y = y - total
        //           => x = 2*y - total
        auto total = accumulate(cbegin(target), cend(target), 0ll);
        priority_queue<int> max_heap(cbegin(target), cend(target));
        while (total != target.size()) {
            const auto y = max_heap.top(); max_heap.pop();
            const auto& remain = total - y;
            auto x = y - remain;
            if (x <= 0) {
                return false;
            }
            if (x > remain) {  // for case [1, 1000000000]
                x = x % remain + remain;
            }
            max_heap.emplace(x);
            total = x + remain;
        }
        return true;
    }

