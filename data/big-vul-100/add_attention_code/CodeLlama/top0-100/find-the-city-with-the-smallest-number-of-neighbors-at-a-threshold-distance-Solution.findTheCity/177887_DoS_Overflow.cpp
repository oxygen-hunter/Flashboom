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


    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dist(n, vector<int>(n, numeric_limits<int>::max()));
        for (const auto& e : edges) {
            dist[e[0]][e[1]] = dist[e[1]][e[0]] = e[2];
        }
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }
        for (int k = 0; k < n; ++k) {
             for (int i = 0; i < n; ++i) {
                 for (int j = 0; j < n; ++j) {
                     if (dist[i][k] != numeric_limits<int>::max() &&
                         dist[k][j] != numeric_limits<int>::max()) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                     }
                 }
             }
        }
        int result = -1, min_num = numeric_limits<int>::max();
        for (int i = n - 1; i >= 0; --i) {
            int num = accumulate(dist[i].cbegin(), dist[i].cend(), 0,
                                 [&distanceThreshold](const auto& a, const auto& b) {
                                     return a + (b <= distanceThreshold);
                                 });
            if (num < min_num) {
                min_num = num;
                result = i;
            }
        }
        return result;
    }


