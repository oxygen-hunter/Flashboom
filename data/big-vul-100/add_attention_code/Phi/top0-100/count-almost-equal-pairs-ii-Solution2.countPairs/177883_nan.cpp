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

    int countPairs(vector<int>& nums) {
        static const int L = 7;
        static const int K = 2;
        vector<int> POW10(L);
        POW10[0] = 1;
        for (int i = 0; i + 1 < L; ++i) {
            POW10[i+1] = POW10[i] * 10;
        }
        const auto& at_most = [&](int k, int x) {
            unordered_set<int> lookup = {x};
            vector<int> result = {x};
            for (int u = 0; k; --k) {
                for (int v = size(result); u < v; ++u) {
                    const int x = result[u];
                    for (int i = 0; i < L; ++i) {
                        const int a = x / POW10[i] % 10;
                        for (int j = i + 1; j < L; ++j) {
                            const int b = x / POW10[j] % 10;
                            if (a == b) {
                                continue;
                            }
                            const int y = x -a * (POW10[i] - POW10[j]) + b * (POW10[i] - POW10[j]);
                            if (lookup.count(y)) {
                                continue;
                            }
                            lookup.emplace(y);
                            result.emplace_back(y);
                        }
                    }
                }
            }
            return result;
        };

        int result = 0;
        unordered_map<int, int> cnt1;
        for (const auto& x : nums) {
            ++cnt1[x];
        }
        unordered_map<int, int> cnt2;
        for (const auto& [x, v] : cnt1) {
            result += cnt2[x] * v + v * (v - 1) / 2;
            for (const auto& x : at_most(K, x)) {
                if (!cnt1.count(x)) {
                    continue;
                }
                cnt2[x] += v;
            }
        }
        return result;
    }

