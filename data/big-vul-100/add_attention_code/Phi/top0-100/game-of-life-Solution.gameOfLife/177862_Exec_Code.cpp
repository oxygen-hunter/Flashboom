restore_page_device(const gs_gstate * pgs_old, const gs_gstate * pgs_new)
 {
     gx_device *dev_old = gs_currentdevice(pgs_old);
     gx_device *dev_new;
    gx_device *dev_t1;
     gx_device *dev_t2;
     bool samepagedevice = obj_eq(dev_old->memory, &gs_int_gstate(pgs_old)->pagedevice,
         &gs_int_gstate(pgs_new)->pagedevice);
 
     if ((dev_t1 = (*dev_proc(dev_old, get_page_device)) (dev_old)) == 0)
        return false;
     /* If we are going to putdeviceparams in a callout, we need to */
     /* unlock temporarily.  The device will be re-locked as needed */
     /* by putdeviceparams from the pgs_old->pagedevice dict state. */
        dev_old->LockSafetyParams = false;
    dev_new = gs_currentdevice(pgs_new);
     dev_new = gs_currentdevice(pgs_new);
     if (dev_old != dev_new) {
         if ((dev_t2 = (*dev_proc(dev_new, get_page_device)) (dev_new)) == 0)
            return false;
        if (dev_t1 != dev_t2)
            return true;
     }
     /*
      * The current implementation of setpagedevice just sets new
      * parameters in the same device object, so we have to check
      * whether the page device dictionaries are the same.
      */
    return !samepagedevice;
 }

    void gameOfLife(vector<vector<int>>& board) {
        const int m = board.size(), n = m ? board[0].size() : 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int count = 0;
                // Count live cells in 3x3 block.
                for (int I = max(i - 1, 0); I < min(i + 2, m); ++I) {
                    for (int J = max(j - 1, 0); J < min(j + 2, n); ++J) {
                        count += board[I][J] & 1;
                    }
                }
                // if (count == 4 && board[i][j]) means:
                //     Any live cell with three live neighbors lives.
                // if (count == 3) means:
                //     Any live cell with two live neighbors.
                //     Any dead cell with exactly three live neighbors lives.
                if ((count == 4 && board[i][j]) || count == 3) {
                    board[i][j] |= 2;  // Mark as live. 
                }
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] >>= 1;  // Update to the next state.
            }
        }
    }

