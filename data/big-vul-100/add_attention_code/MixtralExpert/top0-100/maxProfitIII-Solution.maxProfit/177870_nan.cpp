ztype(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    ref tnref;
    int code = array_get(imemory, op, (long)r_btype(op - 1), &tnref);

    if (code < 0)
        return code;
    if (!r_has_type(&tnref, t_name)) {
         /* Must be either a stack underflow or a t_[a]struct. */
         check_op(2);
         {                       /* Get the type name from the structure. */
            if (op[-1].value.pstruct != 0x00) {
             const char *sname =
                 gs_struct_type_name_string(gs_object_type(imemory,
                                                           op[-1].value.pstruct));
            int code = name_ref(imemory, (const byte *)sname, strlen(sname),
                                (ref *) (op - 1), 0);

            if (code < 0)
                return code;
            } else
                return_error(gs_error_stackunderflow);
        }
        r_set_attrs(op - 1, a_executable);
    } else {
        ref_assign(op - 1, &tnref);
    }
    pop(1);
    return 0;
}


        int maxProfit(vector<int> &prices) {
            const int n = prices.size();

            if(n < 2)
                return 0;

            vector<int> f(n, 0);
            vector<int> g(n, 0);

            for(int i = 1, valley = prices[0]; i < n; ++i) {
                f[i] = max(f[i - 1], prices[i] - valley);
                valley = min(valley, prices[i]);
            }

            for(int i = n - 2, peak = prices[n - 1]; i >= 0; --i) {
                g[i] = max(g[i + 1], peak - prices[i]);
                peak = max(peak, prices[i]);
            }

            int ans = 0;
            for(int i = 0; i < n; ++i) {
                ans = max(ans, f[i] + g[i]);
            }

            return ans;
        }


