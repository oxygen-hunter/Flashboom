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

    int smallestRepunitDivByK(int K) {
        // by observation, K % 2 = 0 or K % 5 = 0, it is impossible
        if (K % 2 == 0 || K % 5 == 0) {
            return -1;
        }
        // let f(N) is a N-length integer only containing digit 1
        // given K % 2 != 0 and K % 5 != 0
        // if there is no N in range (1..K) s.t. f(N) % K = 0
        // => there must be K remainders of f(N) % K in range (1..K-1) excluding 0
        // => due to pigeonhole principle, there must be at least 2 same remainders
        // => there must be some x, y in range (1..K) and x > y s.t. f(x) % K = f(y) % K
        // => (f(x) - f(y)) % K = 0
        // => (f(x-y) * 10^y) % K = 0
        // => due to (x-y) in range (1..K)
        // => f(x-y) % K != 0
        // => 10^y % K = 0
        // => K % 2 = 0 or K % 5 = 0
        // => -><-
        // it proves that there must be some N in range (1..K) s.t. f(N) % K = 0
        int result = 0;
        for (int N = 1; N <= K; ++N) {
            result = (result * 10 + 1) % K;
            if (!result) {
                return N;
            }
        }
        assert(false);
        return -1;  // never reach
    }

