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

    vector<int> beautifulIndices(string s, string a, string b, int k) {
        const auto& KMP = [&](const string& text, const string& pattern) {
            const auto& getPrefix = [&](const string& pattern) {
                vector<int> prefix(pattern.length(), -1);
                int j = -1;
                for (int i = 1; i < pattern.length(); ++i) {
                    while (j > -1 && pattern[j + 1] != pattern[i]) {
                        j = prefix[j];
                    }
                    if (pattern[j + 1] == pattern[i]) {
                        ++j;
                    }
                    prefix[i] = j;
                }
                return prefix;
            };

            vector<int> result;
            const vector<int> prefix = getPrefix(pattern + '#' + text);
            for (int i = (size(pattern) + 1) + (size(pattern) - 1); i < size(prefix); ++i) {
                if (prefix[i] + 1 == size(pattern)) {
                    result.emplace_back((i - (size(pattern) + 1)) - (size(pattern) - 1));
                }
            }
            return result;
        };

        vector<int> result;
        if (!(size(a) <= size(s) && size(b) <= size(s))) {
            return result;
        }
        const auto& lookup = KMP(s, b);
        int j = 0;
        for (const auto& i : KMP(s, a)) {
            const int j = distance(cbegin(lookup), lower_bound(cbegin(lookup), cend(lookup), i - k));
            if (j < size(lookup) && lookup[j] <= i + k) {
                result.emplace_back(i);
            }
        }
        return result;
    }

