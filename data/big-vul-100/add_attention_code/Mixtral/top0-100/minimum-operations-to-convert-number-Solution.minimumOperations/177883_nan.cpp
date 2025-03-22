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

    int minimumOperations(vector<int>& nums, int start, int goal) {
        static const int MAX_X = 1000;

        vector<int> new_nums;
        for (const auto& y : nums) {
            if (y && ((0 <= y && y <= MAX_X) || (0 <= (goal - y) && (goal - y) <= MAX_X) || (0 <= (goal + y) && (goal + y) <= MAX_X) || (0 <= (goal ^ y) && (goal ^ y) <= MAX_X))) {
                new_nums.emplace_back(y);
            }
        }
        nums = move(new_nums);
        vector<pair<int, int>> q = {{start, 0}};
        unordered_set<int> lookup = {start};
        while (!empty(q)) {
            vector<pair<int, int>> new_q;
            for (const auto& [x, steps] : q) {
                for (const auto& y : nums) {
                    for (const auto& nx : {x + y, x - y, x ^ y}) {
                        if (nx == goal) {
                            return steps + 1;
                        }
                        if (!(0 <= nx && nx <= MAX_X) || lookup.count(nx)) {
                            continue;
                        }
                        lookup.emplace(nx);
                        new_q.emplace_back(nx, steps + 1);
                    }
                }
            }
            q = move(new_q);
        }
        return -1;
    }

