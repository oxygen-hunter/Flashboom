hook_print (struct t_weechat_plugin *plugin, struct t_gui_buffer *buffer,
            const char *tags, const char *message, int strip_colors,
            t_hook_callback_print *callback, void *callback_data)
{
    struct t_hook *new_hook;
    struct t_hook_print *new_hook_print;
    
    if (!callback)
        return NULL;
    
    new_hook = malloc (sizeof (*new_hook));
    if (!new_hook)
        return NULL;
    new_hook_print = malloc (sizeof (*new_hook_print));
    if (!new_hook_print)
         {
             rc = (int) (HOOK_CONNECT(ptr_hook, gnutls_cb))
                 (ptr_hook->callback_data, tls_session, req_ca, nreq,
                 pk_algos, pk_algos_len, answer);
             break;
         }
         ptr_hook = ptr_hook->next_hook;
    new_hook->hook_data = new_hook_print;
    new_hook_print->callback = callback;
    new_hook_print->buffer = buffer;
    if (tags)
    {
        new_hook_print->tags_array = string_split (tags, ",", 0, 0,
                                                   &new_hook_print->tags_count);
    }
    else
    {
        new_hook_print->tags_count = 0;
        new_hook_print->tags_array = NULL;
    }
    new_hook_print->message = (message) ? strdup (message) : NULL;
    new_hook_print->strip_colors = strip_colors;
    
    hook_add_to_list (new_hook);
    
    return new_hook;
}

    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> count;
        for(int i = 0; i < size(nums); ++i) {
            ++count[nums[i]];
        }
        int total = (1 << size(quantity)) - 1;
        vector<int> requirement(total + 1);
        for (int mask = 0; mask < size(requirement); ++mask) {  // Time: O(2^m)
            for (int i = 0; i < size(quantity); ++i) {  // Time: O(m)
                if (mask & (1 << i)) {
                    requirement[mask] += quantity[i];
                }
            }
        }
        vector<vector<int>> dp(2, vector<int>(total + 1));
        dp[0][0] = 1;
        int i = 0;
        vector<int> cnts;
        for (const auto& [_, cnt] : count) {
            cnts.emplace_back(cnt);
        }
        if (size(quantity) < size(cnts)) {  // at most use top m cnts
            nth_element(begin(cnts), begin(cnts) + size(quantity) - 1, end(cnts), greater<int>());
            cnts.resize(size(quantity));
        }
        for (int i = 0; i < size(cnts); ++i) {  // Time: O(m)
            dp[(i + 1) % 2] = vector<int>(total + 1);
            // submask enumeration:
            // => sum(nCr(m, k) * 2^k for k in xrange(m+1)) = (1 + 2)^m = 3^m
            // => Time: O(3^m), see https://cp-algorithms.com/algebra/all-submasks.html
            for (int mask = total; mask >= 0; --mask) {
                dp[(i + 1) % 2][mask] |= dp[i % 2][mask];
                for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
                    if (requirement[submask] <= cnts[i] && dp[i % 2][mask ^ submask]) {
                        dp[(i + 1) % 2][mask] = 1;
                    }
                }
            }
        }
        return dp[size(cnts) % 2][total];
    }

