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

    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        static const double PI = atan2(0, -1);

        vector<double> arr;
        int extra = 0;
        for (const auto& p : points) {
            if (p == location) {
                ++extra;
                continue;
            }
            arr.emplace_back(atan2(p[1] - location[1], p[0] - location[0]));
        }
        sort(begin(arr), end(arr));
        const int n = size(arr);
        for (int i = 0; i < n; ++i) {  // make it circular
            arr.emplace_back(arr[i] + 2.0 * PI);
        }
        const double d = 2.0 * PI * (angle / 360.0);
        int result = 0;
        for (int left = 0, right = 0; right < size(arr); ++right) {
            while (arr[right] - arr[left] > d) {
                ++left;
            }
            result = max(result, right - left + 1);
        }
        return result + extra;
    }

