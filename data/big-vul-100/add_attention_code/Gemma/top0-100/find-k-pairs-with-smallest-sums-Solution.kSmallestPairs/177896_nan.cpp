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


    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int>> pairs;
        if (nums1.size() > nums2.size()) {
            vector<pair<int, int>> tmp = kSmallestPairs(nums2, nums1, k);
            for (const auto& pair : tmp) {
                pairs.emplace_back(pair.second, pair.first);
            }
            return pairs;
        }

        using P = pair<int, pair<int, int>>;
        priority_queue<P, vector<P>, greater<P>> q;
        auto push = [&nums1, &nums2, &q](int i, int j) {
            if (i < nums1.size() && j < nums2.size()) {
                q.emplace(nums1[i] + nums2[j], make_pair(i, j));
            }
        };

        push(0, 0);
        while (!q.empty() && pairs.size() < k) {
            auto tmp = q.top(); q.pop();
            int i, j;
            tie(i, j) = tmp.second;
            pairs.emplace_back(nums1[i], nums2[j]);
            push(i, j + 1);
            if (j == 0) {
                push(i + 1, 0);  // at most queue min(m, n) space.
            }
        }
        return pairs; 
    }


