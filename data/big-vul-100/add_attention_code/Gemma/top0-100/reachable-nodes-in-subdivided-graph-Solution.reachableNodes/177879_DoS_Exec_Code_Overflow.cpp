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


    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        using P = pair<int, int>;
        vector<vector<P>> adj(N);
        for (const auto& edge: edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        unordered_map<int, int> best;
        best[0] = 0;
        unordered_map<int, unordered_map<int, int>> count;
        int result = 0;
        priority_queue<P, vector<P>, greater<P>> min_heap;
        min_heap.emplace(0, 0);
        while (!min_heap.empty()) {
            int curr_total, u;
            tie(curr_total, u) = min_heap.top(); min_heap.pop();
            if (best.count(u) && best[u] < curr_total) {
                continue;
            }
            ++result;
            for (const auto& kvp: adj[u]) {
                int v, w;
                tie(v, w) = kvp;
                count[u][v] = min(w, M - curr_total);
                int next_total = curr_total + w + 1;
                if (next_total <= M && 
                    (!best.count(v) || next_total < best[v])) {
                    best[v] = next_total;
                    min_heap.emplace(next_total, v);
                }
            }
        }
        for (const auto& edge: edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            result += min(w, count[u][v] + count[v][u]);
        }
        return result;
    }


