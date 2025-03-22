gs_heap_alloc_bytes(gs_memory_t * mem, uint size, client_name_t cname)
{
    gs_malloc_memory_t *mmem = (gs_malloc_memory_t *) mem;
    byte *ptr = 0;

#ifdef DEBUG
    const char *msg;
    static const char *const ok_msg = "OK";

#  define set_msg(str) (msg = (str))
#else
#  define set_msg(str) DO_NOTHING
#endif

        /* Exclusive acces so our decisions and changes are 'atomic' */
    if (mmem->monitor)
        gx_monitor_enter(mmem->monitor);
    if (size > mmem->limit - sizeof(gs_malloc_block_t)) {
        /* Definitely too large to allocate; also avoids overflow. */
        set_msg("exceeded limit");
     } else {
         uint added = size + sizeof(gs_malloc_block_t);
 
        if (mmem->limit - added < mmem->used)
             set_msg("exceeded limit");
         else if ((ptr = (byte *) Memento_label(malloc(added), cname)) == 0)
             set_msg("failed");
        else {
            gs_malloc_block_t *bp = (gs_malloc_block_t *) ptr;

            /*
             * We would like to check that malloc aligns blocks at least as
             * strictly as the compiler (as defined by ARCH_ALIGN_MEMORY_MOD).
             * However, Microsoft VC 6 does not satisfy this requirement.
             * See gsmemory.h for more explanation.
             */
            set_msg(ok_msg);
            if (mmem->allocated)
                mmem->allocated->prev = bp;
            bp->next = mmem->allocated;
            bp->prev = 0;
            bp->size = size;
            bp->type = &st_bytes;
            bp->cname = cname;
            mmem->allocated = bp;
            ptr = (byte *) (bp + 1);
            mmem->used += size + sizeof(gs_malloc_block_t);
            if (mmem->used > mmem->max_used)
                mmem->max_used = mmem->used;
        }
    }
    if (mmem->monitor)
        gx_monitor_leave(mmem->monitor);	/* Done with exclusive access */
    /* We don't want to 'fill' under mutex to keep the window smaller */
    if (ptr)
        gs_alloc_fill(ptr, gs_alloc_fill_alloc, size);
#ifdef DEBUG
    if (gs_debug_c('a') || msg != ok_msg)
        dmlprintf6(mem, "[a+]gs_malloc(%s)(%u) = 0x%lx: %s, used=%ld, max=%ld\n",
                   client_name_string(cname), size, (ulong) ptr, msg, mmem->used, mmem->max_used);
#endif
    return ptr;
#undef set_msg
}

    int maximumMinutes(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> directions{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        enum State {FIRE = 1, WALL, PERSON};
        const int INF = 1e9;
        const auto& bfs = [&]() {
            unordered_map<int, vector<vector<int>>> time;
            time[FIRE] = vector<vector<int>>(size(grid), vector<int>(size(grid[0]), INF));
            time[PERSON] = vector<vector<int>>(size(grid), vector<int>(size(grid[0]), INF));
            vector<tuple<int, int, int>> q;
            for (int r = 0; r < size(grid); ++r) {
                for (int c = 0; c < size(grid[0]); ++c) {
                    if (grid[r][c] == FIRE) {
                        q.emplace_back(r, c, FIRE);
                    }
                }
            }
            q.emplace_back(0, 0, PERSON);
            for (const auto& [r, c, t] : q) {
                time[t][r][c] = 0;
            }
            for (int d = 0; !empty(q); ++d) {
                vector<tuple<int, int, int>> new_q;
                for (const auto& [r, c, t] : q) {
                    for (const auto& [dr, dc] : directions) {
                        const int nr = r + dr, nc = c + dc;
                        if (!(0 <= nr && nr < size(grid) && 0 <= nc && nc < size(grid[0]) &&
                              grid[nr][nc] != WALL && time[t][nr][nc] == INF &&
                              (t == FIRE ||
                               d + 1 < time[FIRE][nr][nc] || (d + 1 == time[FIRE][nr][nc] && nr == size(grid) - 1 && nc == size(grid[0]) - 1)))) {
                            continue;
                        }
                        time[t][nr][nc] = d + 1;
                        new_q.emplace_back(nr, nc, t);
                    }
                }
                q = move(new_q);
            }
            return time;
        };
        auto time = bfs();
        if (time[PERSON][size(grid) - 1][size(grid[0]) - 1] == INF) {
            return -1;
        }
        if (time[FIRE][size(grid) - 1][size(grid[0]) - 1] == INF) {
            return INF;
        }
        const int diff = time[FIRE][size(grid) - 1][size(grid[0]) - 1] - time[PERSON][size(grid) - 1][size(grid[0]) - 1];
        return (time[FIRE][size(grid) - 1][size(grid[0]) - 2] - time[PERSON][size(grid) - 1][size(grid[0]) - 2] == diff + 2 ||
                time[FIRE][size(grid) - 2][size(grid[0]) - 1] - time[PERSON][size(grid) - 2][size(grid[0]) - 1] == diff + 2)
               ? diff
               : diff - 1;
    }

