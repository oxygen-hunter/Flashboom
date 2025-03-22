static void become_daemon(const char *pidfile)
{
#ifndef _WIN32
    pid_t pid, sid;

    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (pidfile) {
        if (!ga_open_pidfile(pidfile)) {
            g_critical("failed to create pidfile");
            exit(EXIT_FAILURE);
         }
     }
 
    umask(0);
     sid = setsid();
     if (sid < 0) {
         goto fail;
    }
    if ((chdir("/")) < 0) {
        goto fail;
    }

    reopen_fd_to_null(STDIN_FILENO);
    reopen_fd_to_null(STDOUT_FILENO);
    reopen_fd_to_null(STDERR_FILENO);
    return;

fail:
    if (pidfile) {
        unlink(pidfile);
    }
    g_critical("failed to daemonize");
    exit(EXIT_FAILURE);
#endif
}

    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        vector<vector<int>> adj(size(cost));
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1]);
            adj[e[1]].emplace_back(e[0]);
        }
        vector<long long> result(size(cost));
        const auto& iter_dfs = [&]() {
            vector<long long> result(size(cost));
            using RET = vector<int64_t>;
            RET ret = {cost[0]};
            vector<tuple<int, int, int, int, shared_ptr<RET>, RET *>> stk = {{1, 0, -1, -1, nullptr, &ret}};
            while (!stk.empty()) {
                const auto [step, u, p, i, new_ret, ret] = stk.back(); stk.pop_back();
                if (step == 1) {
                    stk.emplace_back(4, u, -1, -1, nullptr, ret);
                    stk.emplace_back(2, u, p, 0, nullptr, ret);
                } else if (step == 2) {
                    if (i == size(adj[u])) {
                        continue;
                    }
                    const auto& v = adj[u][i];
                    stk.emplace_back(2, u, p, i + 1, new_ret, ret);
                    if (v == p) {
                        continue;
                    }
                    const auto& new_ret = make_shared<RET>(RET{cost[v]});
                    stk.emplace_back(3, -1, -1, -1, new_ret, ret);
                    stk.emplace_back(1, v, u, -1, nullptr, new_ret.get());
                } else if (step == 3) {
                    for (const auto& c : *new_ret) {
                        ret->emplace_back(c);
                    }
                    sort(begin(*ret), end(*ret));
                    if (size(*ret) > 5) {
                        ret->assign({(*ret)[0], (*ret)[1], (*ret)[size(*ret) - 3], (*ret)[size(*ret) - 2], (*ret)[size(*ret) - 1]});
                    }
                } else if (step == 4) {
                    result[u] = size(*ret) < 3 ? 1 : max({(*ret)[0] * (*ret)[1] * (*ret)[size(*ret) - 1], (*ret)[size(*ret) - 3] * (*ret)[size(*ret) - 2] * (*ret)[size(*ret) - 1], static_cast<int64_t>(0)});
                }
            }
            return result;
        };

        return iter_dfs();
    }

