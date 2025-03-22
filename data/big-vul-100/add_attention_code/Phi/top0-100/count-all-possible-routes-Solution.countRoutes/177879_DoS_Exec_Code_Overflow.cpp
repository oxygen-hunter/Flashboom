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

    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        static const int MOD = 1e9 + 7;

        int s = locations[start];
        int f = locations[finish];
        sort(begin(locations), end(locations));
        start = distance(cbegin(locations), lower_bound(cbegin(locations), cend(locations), s));
        finish = distance(cbegin(locations), lower_bound(cbegin(locations), cend(locations), f));

        vector<vector<int>> left(locations.size(), vector<int>(fuel + 1));  // left[i][f], last move is toward left to location i by f fuel
        vector<vector<int>> right(locations.size(), vector<int>(fuel + 1));  // right[i][f], last move is toward right to location i by f fuel
        for (int f = 1; f <= fuel; ++f) {
            for (int j = 0; j < locations.size() - 1; ++j) {
                int d = locations[j + 1] - locations[j];
                if (f > d) {
                    // left[j][f] = right[j+1][f-d(j, j+1)] + 2*right[j+2][f-d(j, j+2)] + ... + 2^(k-1)*right[j+k][f-d(j, j+k)]
                    // => left[j+1][f] = (ight[j+2][f-d(j+1, j+2)] + 2*right[j+3][f-d(j+1, j+3)] + ... + 2^(k-2)*right[j+1+k-1][f-d(j+1, j+1+k-1)]
                    // => left[j+1][f-d(j, j+1)] = right[j+2][f-d(j, j+2)] + 2*right[j+3][f-d(j, j+3)] + ... + 2^(k-2)*right[j+k][f-d(j, j+k)]
                    // => left[j][f] = right[j+1][f-d(j, j+1)] + 2*left[j+1][f-d(j, j+1)]
                    left[j][f] = (right[j + 1][f - d] + 2 * left[j + 1][f - d] % MOD) % MOD;
                } else if (f == d) {
                    left[j][f] = int(j + 1 == start);
                }
            }
            for (int j = 1; j < locations.size(); ++j) {
                int d = locations[j] - locations[j - 1];
                if (f > d) {
                    // right[j][f] = left[j-1][f-d(j, j-1)] + 2*left[j-2][f-d(j, j-2)] + ... + 2^(k-1)*left[j-k][f-d(j, j-k)]
                    // => right[j-1][f] = left[j-2][f-d(j-1, j-2)] + 2*left[j-3][f-d(j-1, j-3)] + ... + 2^(k-2)*left[j-1-k+1][f-d(j-1, j-1-k+1)]
                    // => right[j-1][f-d(j, j-1)] = left[j-2][f-d(j, j-2)] + 2*left[j-3][f-d(j, j-3)] + ... + 2^(k-2)*left[j-k][f-d(j, j-k)]
                    // => right[j][f] = left[j-1][f-d(j, j-1)] + 2*right[j-1][f-d(j, j-1)]
                    right[j][f] = (left[j - 1][f - d] + 2 * right[j - 1][f - d] % MOD) % MOD;
                } else if (f == d) {
                    right[j][f] = int(j - 1 == start);
                }
            }
        }
        int result = int(start == finish);
        for (int f = 1; f <= fuel; ++f) {
            result = ((result + left[finish][f]) % MOD + right[finish][f]) % MOD;
        }
        return result;
    }

