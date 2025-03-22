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


        bool searchMatrix(vector<vector<int> > &matrix, int target) {
            if(matrix.empty()) return false;

            const size_t m = matrix.size();
            const size_t n = matrix.front().size();

            int start = 0, end = m * n;

            while(start < end) {
                int mid = (start + end) / 2;
                int value = matrix[mid / n][mid % n];
                if(target == value)
                    return true;
                else if (value < target)
                    start = mid + 1;
                else
                    end = mid;
            }
            return false;
        }


