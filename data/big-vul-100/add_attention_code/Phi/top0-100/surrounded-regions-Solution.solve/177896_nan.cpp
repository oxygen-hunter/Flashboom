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

    void solve(vector<vector<char>>& board) {
        if (board.empty()) {
            return;
        }

        queue<pair<int, int>> q;
        for (int i = 0; i < board.size(); ++i) {
            if (board[i][0] == 'O') {
                board[i][0] = 'V';
                q.emplace(i, 0);
            }
            if (board[i][board[0].size() - 1] == 'O') {
                board[i][board[0].size() - 1] = 'V';
                q.emplace(i, board[0].size() - 1);
            }
        }

        for (int j = 1; j < board[0].size() - 1; ++j) {
            if (board[0][j] == 'O') {
                board[0][j] = 'V';
                q.emplace(0, j);
            }
            if (board[board.size() - 1][j] == 'O') {
                board[board.size() - 1][j] = 'V';
                q.emplace(board.size() - 1, j);
            }
        }
        while (!q.empty()) {
            int i, j;
            tie(i, j) = q.front();
            q.pop();
            static const vector<pair<int, int>> directions{{0, -1}, {0, 1},
                                                           {-1, 0}, {1, 0}};
            for (const auto& d : directions) {
                const int x = i + d.first, y = j + d.second;
                if (0 <= x && x < board.size() &&
                    0 <= y && y < board[0].size() &&
                    board[x][y] == 'O') {
                    board[x][y] = 'V';
                    q.emplace(x, y);
                }
            }
        }
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] != 'V') {
                    board[i][j] = 'X';
                } else {
                    board[i][j] = 'O';
                }
            }
        }
    }

