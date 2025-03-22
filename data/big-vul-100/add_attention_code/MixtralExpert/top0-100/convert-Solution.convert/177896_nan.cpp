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


        string convert(string s, int nRows) {
            vector<string> row(nRows);
            string ans;
            int cnt = 0;

            if(nRows == 1)
                return s;

            for(auto c : s) {
                if(cnt < nRows) {
                    row[cnt].push_back(c);
                }
                else {
                    row[2 * nRows - 2 - cnt].push_back(c);
                }

                cnt = (cnt + 1) % (2 * nRows - 2);
            }

            for(auto s : row) {
                ans.append(s);
            }

            return ans;
        }


