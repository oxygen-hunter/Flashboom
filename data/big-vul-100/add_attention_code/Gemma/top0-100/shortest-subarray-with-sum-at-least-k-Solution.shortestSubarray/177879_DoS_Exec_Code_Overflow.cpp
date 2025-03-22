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


    int shortestSubarray(vector<int>& A, int K) {
        vector<int> accumulated_sum(A.size() + 1, 0);
        partial_sum(A.cbegin(), A.cend(), next(accumulated_sum.begin()), plus<int>());
        
        int result = numeric_limits<int>::max();
        deque<int> mono_increasing_q;
        for (int i = 0; i < accumulated_sum.size(); ++i) {
            while (!mono_increasing_q.empty() &&
                   accumulated_sum[i] <= accumulated_sum[mono_increasing_q.back()]) {
                mono_increasing_q.pop_back();
            }
            while (!mono_increasing_q.empty() &&
                   accumulated_sum[i] - accumulated_sum[mono_increasing_q.front()] >= K) {
                result = min(result, i - mono_increasing_q.front());
                mono_increasing_q.pop_front();
            }
            mono_increasing_q.emplace_back(i);
        }
        return result != numeric_limits<int>::max() ? result : -1;
    }


