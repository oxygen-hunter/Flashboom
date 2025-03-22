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


    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        const auto& next_popcount = [](uint32_t n) {  // reference: https://massivealgorithms.blogspot.com/2014/06/hakmem-item-175.html
            const uint32_t lowest_bit = n & -n;
            const uint32_t left_bits = n + lowest_bit;
            const uint32_t changed_bits = n ^ left_bits;
            const uint32_t right_bits = (changed_bits / lowest_bit) >> 2;
            return left_bits | right_bits;
        };

        vector<uint32_t> masks(size(matrix));
        for (int r = 0; r < size(matrix); ++r) {
            uint32_t m = 0;
            for (int c = 0; c < size(matrix[0]); ++c) {
                m |= matrix[r][c] << ((size(matrix[0]) - 1) - c);
            }
            masks[r] = m;
        }
        int result = 0;
        for (uint32_t mask = (1 << numSelect) - 1; mask < 1 << size(matrix[0]); mask = next_popcount(mask)) {
            const int cnt = accumulate(cbegin(masks), cend(masks), 0, [&](const auto& total, const auto& x) {
                return total + static_cast<int>((x & mask) == x);
            });
            result = max(result, cnt);
        }
        return result;
    }


