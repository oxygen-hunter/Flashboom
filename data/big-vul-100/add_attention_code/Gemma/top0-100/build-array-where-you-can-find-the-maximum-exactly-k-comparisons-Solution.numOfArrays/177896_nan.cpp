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


    int numOfArrays(int n, int m, int k) {
        static const int MOD = 1e9 + 7;
        // dp[l][i][j] = number of ways of constructing array length l with max element i at search cost j
        vector<vector<vector<uint64_t>>> dp(2, vector<vector<uint64_t>>(m + 1, vector<uint64_t>(k + 1)));
        // prefix_dp[l][i][j] = sum(dp[l][i][j] for i in [1..i])
        vector<vector<vector<uint64_t>>> prefix_dp(2, vector<vector<uint64_t>>(m + 1, vector<uint64_t>(k + 1)));
        for (uint64_t i = 1; i <= m; ++i) {
            dp[1][i][1] = 1;
            prefix_dp[1][i][1] = (prefix_dp[1][i - 1][1] + dp[1][i][1]) % MOD;
        }
        for (uint64_t l = 2; l <= n; ++l) {
            for (uint64_t i = 1; i <= m; ++i) {
                for (uint64_t j = 1; j <= k; ++j) {
                    dp[l % 2][i][j] = (i * dp[(l - 1) % 2][i][j] % MOD + prefix_dp[(l - 1) % 2][i - 1][j - 1]) % MOD;
                    prefix_dp[l % 2][i][j] = (prefix_dp[l % 2][i - 1][j] + dp[l % 2][i][j]) % MOD;
                }
            }
        }
        return prefix_dp[n % 2][m][k];
    }


