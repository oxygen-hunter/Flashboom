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

    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        vector<tuple<int, bool, int>> events;
        for (int i = 0; i < size(times); ++i) {
            events.emplace_back(times[i][0], true, i);
            events.emplace_back(times[i][1], false, i);
        }
        sort(begin(events), end(events));

        unordered_map<int, int> lookup;
        priority_queue<int, vector<int>, greater<int>> min_heap;
        for (const auto& [_, arrival, i] : events) {
            if (!arrival) {
                min_heap.emplace(lookup[i]);
                lookup.erase(i);
                continue;
            }
            if (!empty(min_heap)) {
                lookup[i] = min_heap.top(); min_heap.pop();
            } else {
                lookup[i] = size(lookup);
            }
            if (i == targetFriend) {
                break;
            }
        }
        return lookup[targetFriend];
    }

