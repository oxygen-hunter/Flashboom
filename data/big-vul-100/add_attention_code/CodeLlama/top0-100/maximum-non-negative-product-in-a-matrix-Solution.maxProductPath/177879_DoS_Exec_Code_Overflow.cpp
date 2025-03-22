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


    int maxProductPath(vector<vector<int>>& grid) {
        static const int MOD = 1e9 + 7;
        vector<vector<int64_t>> max_dp(2, vector<int64_t>(size(grid[0])));
        vector<vector<int64_t>> min_dp(2, vector<int64_t>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                if (i == 0 && j == 0) {
                    max_dp[0][0] = min_dp[0][0] = grid[0][0];
                    continue;
                }
                auto curr_max = max(i > 0 ? max_dp[(i - 1) % 2][j] : max_dp[i % 2][j - 1],
                                    j > 0 ? max_dp[i % 2][j - 1] : max_dp[(i - 1) % 2][j]);
                auto curr_min = min(i > 0 ? min_dp[(i - 1) % 2][j] : min_dp[i % 2][j - 1],
                                    j > 0 ? min_dp[i % 2][j - 1] : min_dp[(i - 1) % 2][j]);
                if (grid[i][j] < 0) {
                    swap(curr_max, curr_min);
                }
                max_dp[i % 2][j] = curr_max * grid[i][j];
                min_dp[i % 2][j] = curr_min * grid[i][j];
            }
        }
        return max_dp[(size(grid) - 1) % 2].back() >= 0 ? max_dp[(size(grid) - 1) % 2].back() % MOD : -1;
    }


