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

    vector<int> filterRestaurants(vector<vector<int>>& restaurants, int veganFriendly, int maxPrice, int maxDistance) {
        vector<int> result;
        unordered_map<int, int> lookup;
        for (int i = 0; i < restaurants.size(); ++i) {
            const auto& r = restaurants[i];
            if (r[2] >= veganFriendly && r[3] <= maxPrice && r[4] <= maxDistance) {
                lookup[r[0]] = i;  
                result.emplace_back(r[0]);
            }
        }
        sort(result.begin(), result.end(),
             [&restaurants, &lookup](const auto& i, const auto& j) {
                 return vector<int>{-restaurants[lookup[i]][1], -restaurants[lookup[i]][0]} <
                        vector<int>{-restaurants[lookup[j]][1], -restaurants[lookup[j]][0]};
             });
        return result;
    }

