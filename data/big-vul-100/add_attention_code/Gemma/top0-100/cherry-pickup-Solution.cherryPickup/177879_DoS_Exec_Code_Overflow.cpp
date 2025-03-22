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


    int cherryPickup(vector<vector<int>>& grid) {
        // dp holds the max # of cherries two k-length paths can pickup.
        // The two k-length paths arrive at (i, k - i) and (j, k - j), 
        // respectively.
        const int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        dp[0][0] = grid[0][0];

        const int max_len = 2 * (n - 1);
        for (int k = 1; k <= max_len; ++k) {
            for (int i = min(k, n - 1); i >= max(0, k - n + 1); --i) {  // 0 <= i < n, 0 <= k-i < n
                for (int j = min(k , n - 1); j >= i; --j) {             // i <= j < n, 0 <= k-j < n
                    if (grid[i][k - i] == -1 ||
                        grid[j][k - j] == -1) {
                        dp[i][j] = -1;
                        continue;
                    }
                    int cnt = grid[i][k - i] + ((i == j) ? 0 : grid[j][k - j]);
                    int max_cnt = -1;
                    static const vector<pair<int, int>> directions{{0, 0}, {-1, 0}, {0, -1}, {-1, -1}};
                    for (const auto& direction : directions) {
                        const auto ii = i + direction.first;
                        const auto jj = j + direction.second;
                        if (ii >= 0 && jj >= 0 && dp[ii][jj] >= 0) {
                            max_cnt = max(max_cnt, dp[ii][jj] + cnt);
                        }
                    }
                    dp[i][j] = max_cnt;
                }
            }
        }
        return max(dp[n - 1][n - 1], 0);
    }


