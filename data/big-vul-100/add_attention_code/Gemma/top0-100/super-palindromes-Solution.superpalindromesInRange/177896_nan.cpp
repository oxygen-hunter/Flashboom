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


    int superpalindromesInRange(string L, string R) {
        const auto K = static_cast<int>(pow(10, (R.length() + 1) * 0.25));
        const int64_t l = stol(L), r = stol(R);
        int result = 0;

        // count odd length
        for (int k = 0; k < K; ++k) {
            const string s = to_string(k), rev_s(s.rbegin(), s.rend());
            int64_t v = stol(s + rev_s.substr(1));
            v *= v;
            if (v > r) {
                break;
            }
            if (v >= l && is_palindrome(v)) {
                ++result;
            }
        }

        // count even length
        for (int k = 0; k < K; ++k) {
            const string s = to_string(k), rev_s(s.rbegin(), s.rend());
            int64_t v = stol(s + rev_s);
            v *= v;
            if (v > r) {
                break;
            }
            if (v >= l && is_palindrome(v)) {
                ++result;
            }
        }

        return result;
    }


