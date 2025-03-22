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

    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        vector<vector<int>> adj(size(patience));
        for (auto &edge : edges) {
            adj[edge[0]].emplace_back(edge[1]);
            adj[edge[1]].emplace_back(edge[0]);
        }
        vector<bool> lookup(size(patience));
        lookup[0] = true;
        vector<int> q{{0}};
        int result = 0, step = 1;
        while (!empty(q)) {
            vector<int> new_q;
            for (const auto& u : q) {
                for (const auto& v : adj[u]) {
                    if (lookup[v]) {
                        continue;
                    }
                    lookup[v] = true;
                    new_q.emplace_back(v);
                    result = max(result, ((step * 2) - 1) / patience[v] * patience[v] + (step * 2));
                }
            }
            q = move(new_q);
            ++step;
        }
        return 1 + result;
    }

