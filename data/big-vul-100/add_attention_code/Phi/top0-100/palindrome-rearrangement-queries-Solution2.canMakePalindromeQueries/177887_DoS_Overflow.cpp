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

    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        vector<int> prefix(size(s) / 2 + 1);
        vector<vector<int>> prefixs1(size(s) / 2 + 1, vector<int>(26));
        vector<vector<int>> prefixs2(size(s) / 2 + 1, vector<int>(26));
        for (int i = 0; i < size(s) / 2; ++i) {
            const int x = s[i] - 'a', y = s[(size(s) - 1) - i] - 'a';
            prefix[i + 1] = prefix[i] + (x != y ? 1 : 0);
            for (int j = 0; j < 26; ++j) {
                prefixs1[i + 1][j] = prefixs1[i][j] + (j == x ? 1 : 0);
                prefixs2[i + 1][j] = prefixs2[i][j] + (j == y ? 1 : 0);
            }
        }
    
        const auto& check = [&](int left1, int right1, int left2, int right2) {
            const auto& same = [&](int left, int right) {
                for (int i = 0; i < 26; ++i) {
                    if ((prefixs1[right + 1][i] - prefixs1[left][i]) - (prefixs2[right + 1][i] - prefixs1[left][i]) != 0) {
                        return false;
                    }
                }
                return true;
            };

            const auto& min_left = min(left1, left2), &max_left = max(left1, left2);
            const auto& min_right = min(right1, right2), &max_right = max(right1, right2);
            if (!(prefix[min_left] - prefix[0] == 0 && prefix.back() - prefix[max_right + 1] == 0)) {
                return false;
            }
            if (min_right < max_left) {  // non-overlapped
                return prefix[max_left] - prefix[min_right + 1] == 0 && same(min_left, min_right) && same(max_left, max_right);
            }
            // overlapped
            if ((left1 == min_left) == (right1 == max_right)) {  // inside another
                return same(min_left, max_right);
            }
            // not inside another
            auto p1 = &prefixs1, p2 = &prefixs2;
            if (min_left != left1) {
                swap(p1, p2);
            }
            for (int i = 0; i < 26; ++i) {
                const int d1 = ((*p1)[min_right + 1][i] - (*p1)[min_left][i]) - ((*p2)[max_left][i] - (*p2)[min_left][i]);
                const int d2 = ((*p2)[max_right + 1][i] - (*p2)[max_left][i]) - ((*p1)[max_right + 1][i] - (*p1)[min_right + 1][i]);
                if (!(d1 == d2 && d1 >= 0)) {  // test case: s = "aabbba", queries = [[0,1,3,4]]
                    return false;
                }
            }
            return true;
        };
    
        vector<bool> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = check(queries[i][0], queries[i][1], (size(s) - 1) - queries[i][3], (size(s) - 1) - queries[i][2]);
        }
        return result;
    }

