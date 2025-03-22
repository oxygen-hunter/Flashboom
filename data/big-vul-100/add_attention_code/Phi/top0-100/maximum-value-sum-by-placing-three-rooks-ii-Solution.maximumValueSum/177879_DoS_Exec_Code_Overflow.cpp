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

    long long maximumValueSum(vector<vector<int>>& board) {
        static const int k = 3;
    
        const auto& combinations = [](int n, int k, const auto& callback) {
            static const auto& next_pos =
                [](const auto& n, const auto& k, const auto& idxs) {
                    int i = k - 1;
                    for (; i >= 0; --i) {
                        if (idxs[i] != i + n - k) {
                            break;
                        }
                    }
                    return i;
                };
        
            vector<int> idxs(k);
            iota(begin(idxs), end(idxs), 0);
            callback(idxs);
            for (int i; (i = next_pos(n, k, idxs)) >= 0;) {
                ++idxs[i];
                for (int j = i + 1; j < k; ++j) {
                    idxs[j] = idxs[j - 1] + 1;
                }
                callback(idxs);
            }
        };
    
        using Data = tuple<int, int, int>;
        vector<priority_queue<Data, vector<Data>, greater<Data>>> min_heaps(size(board[0]));
        for (int i = 0; i < size(board); ++i) {
            priority_queue<Data, vector<Data>, greater<Data>> min_heap;
            for (int j = 0; j < size(board[0]); ++j) {
                min_heap.emplace(board[i][j], i, j);
                if (size(min_heap) == k + 1) {
                    min_heap.pop();
                }
            }
            while (!empty(min_heap)) {
                const auto [v, i, j] = min_heap.top(); min_heap.pop();
                min_heaps[j].emplace(v, i, j);
                if (size(min_heaps[j]) == k + 1) {
                    min_heaps[j].pop();
                }
            }
        }
        priority_queue<Data, vector<Data>, greater<Data>> min_heap;
        for (auto& h : min_heaps) {
            while (!empty(h)) {
                const auto x = h.top(); h.pop();
                min_heap.emplace(x);
                if (size(min_heap) == ((k - 1) * (2 * k - 1) + 1) + 1) {  // each choice excludes at most 2k-1 candidates, we should have at least (k-1)*(2k-1)+1 candidates
                    min_heap.pop();
                }
            }
        }
        int64_t result = numeric_limits<int64_t>::min();
        vector<Data> candidates;
        while (!empty(min_heap)) {
            const auto x = min_heap.top(); min_heap.pop();
            candidates.emplace_back(x);
        }
        combinations(size(candidates), k, 
                     [&](const vector<int>& idxs) {
                        const auto& [x0, x1, x2] = candidates[idxs[0]];
                        const auto& [y0, y1, y2] = candidates[idxs[1]];
                        const auto& [z0, z1, z2] = candidates[idxs[2]];
                        if ((x1 != y1 && y1 != z1 && z1 != x1) &&
                            (x2 != y2 && y2 != z2 && z2 != x2)) {
                            result = max(result, static_cast<int64_t>(x0) + y0 + z0);
                        }
                     });
        return result;
    }

