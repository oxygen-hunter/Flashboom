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

    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        vector<int64_t> diffs(size(nums1));
        for (int i = 0; i < size(diffs); ++i) {
            diffs[i] = abs(nums1[i] - nums2[i]);
        }
        sort(rbegin(diffs), rend(diffs));
        int64_t k = min(static_cast<int64_t>(k1) + k2, accumulate(cbegin(diffs), cend(diffs), static_cast<int64_t>(0)));
        const auto& check = [&](int x) {
            return accumulate(cbegin(diffs), cend(diffs), 0ll,
                              [&](const auto& total, const auto& d) {
                                  return total + max(d - x, static_cast<int64_t>(0));
                              }) <= k;
        };
        int64_t left = 0, right = diffs[0];
        while (left <= right) {
            const int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        k -= accumulate(cbegin(diffs), cend(diffs), 0ll,
                        [&](const auto& total, const auto& d) {
                            return total + max(d - left, static_cast<int64_t>(0));
                        });
        for (int i = 0; i < size(diffs); ++i) {
            diffs[i] = min(diffs[i], left) - int(i < k);
        }
        return accumulate(cbegin(diffs), cend(diffs), 0ll,
                          [](const auto& total, const auto& d) {
                              return total + d * d;
                          });
    }

