static uint32_t fdctrl_read_data(FDCtrl *fdctrl)
 {
     FDrive *cur_drv;
     uint32_t retval = 0;
    int pos;
 
     cur_drv = get_cur_drv(fdctrl);
     fdctrl->dsr &= ~FD_DSR_PWRDOWN;
    if (!(fdctrl->msr & FD_MSR_RQM) || !(fdctrl->msr & FD_MSR_DIO)) {
        FLOPPY_DPRINTF("error: controller not ready for reading\n");
         return 0;
     }
     pos = fdctrl->data_pos;
     if (fdctrl->msr & FD_MSR_NONDMA) {
        pos %= FD_SECTOR_LEN;
         if (pos == 0) {
             if (fdctrl->data_pos != 0)
                 if (!fdctrl_seek_to_next_sect(fdctrl, cur_drv)) {
                    FLOPPY_DPRINTF("error seeking to next sector %d\n",
                                   fd_sector(cur_drv));
                    return 0;
                }
            if (blk_read(cur_drv->blk, fd_sector(cur_drv), fdctrl->fifo, 1)
                < 0) {
                FLOPPY_DPRINTF("error getting sector %d\n",
                               fd_sector(cur_drv));
                /* Sure, image size is too small... */
                memset(fdctrl->fifo, 0, FD_SECTOR_LEN);
            }
        }
    }
    retval = fdctrl->fifo[pos];
    if (++fdctrl->data_pos == fdctrl->data_len) {
        fdctrl->data_pos = 0;
        /* Switch from transfer mode to status mode
         * then from status mode to command mode
         */
        if (fdctrl->msr & FD_MSR_NONDMA) {
            fdctrl_stop_transfer(fdctrl, 0x00, 0x00, 0x00);
        } else {
            fdctrl_reset_fifo(fdctrl);
            fdctrl_reset_irq(fdctrl);
        }
    }
    FLOPPY_DPRINTF("data register: 0x%02x\n", retval);

    return retval;
}


    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        const int R = size(grid), C = size(grid[0]);
        const int N = R * C;
        unordered_set<int> WALLS;
        int FOOD = -1, MOUSE_START = -1, CAT_START = -1;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (grid[r][c] == 'M') {
                    MOUSE_START = r * C + c;
                } else if (grid[r][c] == 'C') {
                    CAT_START = r * C + c;
                } else if (grid[r][c] == 'F') {
                    FOOD = r * C + c;
                } else if (grid[r][c] == '#') {
                    WALLS.emplace(r * C + c);
                }
            }
        }

        vector<vector<vector<int>>> graph(N, vector<vector<int>>(2));
        vector<int> jump = {mouseJump, catJump};
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (grid[r][c] == '#') {
                    continue;
                }
                int pos = r * C + c;
                for (const auto& t : {MOUSE, CAT}) {
                    for (const auto& [dr, dc] : directions) {
                        for (int d = 0; d <= jump[t - 1]; ++d) {
                            int nr = r + dr * d, nc = c + dc * d;
                            if (!(0 <= nr && nr < R && 0 <= nc && nc < C && grid[nr][nc] != '#')) {
                                break;
                            }
                            graph[pos][t - 1].emplace_back(nr * C + nc);
                        }
                    }
                }
            }
        }

        vector<vector<vector<int>>> degree(N, vector<vector<int>>(N, vector<int>(2)));
        for (int m = 0; m < size(graph); ++m) {
            for (int c = 0; c < size(graph); ++c) {
                // degree[m][c][MOUSE - 1] = size(graph[m][MOUSE - 1]);
                degree[m][c][CAT - 1] = size(graph[c][CAT - 1]);
            }
        }

        vector<vector<vector<int>>> color(N, vector<vector<int>>(N, vector<int>(2)));
        queue<tuple<int, int, int>> q1;
        // queue<tuple<int, int, int>> q2;
        for (int i = 0; i < size(graph); ++i) {
            if (WALLS.count(i) || i == FOOD) {
                continue;
            }
            color[FOOD][i][CAT - 1] = MOUSE;
            q1.emplace(FOOD, i, CAT);
            color[i][FOOD][MOUSE - 1] = CAT;
            // q2.emplace(i, FOOD, MOUSE);
            for (const auto& t : {MOUSE, CAT}) {
                color[i][i][t - 1] = CAT;
                // q2.emplace(i, i, t);
            }
        }
        while (!empty(q1)) {
            const auto [i, j, t] = q1.front(); q1.pop();
            for (const auto& [ni, nj, nt] : parents(graph, i, j, t)) {
                if (color[ni][nj][nt - 1] != DRAW) {
                    continue;
                }
                if (t == CAT) {
                    color[ni][nj][nt - 1] = MOUSE;
                    q1.emplace(ni, nj, nt);
                    continue;
                }
                --degree[ni][nj][nt - 1];
                if (!degree[ni][nj][nt - 1]) {
                    color[ni][nj][nt - 1] = MOUSE;
                    q1.emplace(ni, nj, nt);
                }
            }
        }
        // while (!empty(q2)) {
        //     const auto [i, j, t] = q2.front(); q2.pop();
        //     for (const auto& [ni, nj, nt] : parents(graph, i, j, t)) {
        //         if (color[ni][nj][nt - 1] != DRAW) {
        //             continue;
        //         }
        //         if (t == MOUSE) {
        //             color[ni][nj][nt - 1] = CAT;
        //             q2.emplace(ni, nj, nt);
        //             continue;
        //         }
        //         --degree[ni][nj][nt - 1];
        //         if (!degree[ni][nj][nt - 1]) {
        //             color[ni][nj][nt - 1] = CAT;
        //             q2.emplace(ni, nj, nt);
        //         }
        //     }
        // }
        return color[MOUSE_START][CAT_START][MOUSE - 1] == MOUSE;
    }


