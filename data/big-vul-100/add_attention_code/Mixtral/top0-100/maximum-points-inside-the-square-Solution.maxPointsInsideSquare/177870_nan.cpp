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

    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        static const int INF = numeric_limits<int>::max();
    
        vector<int> lookup(26, INF);
        int d = INF;
        for (int i = 0; i < size(s); ++i) {
            int mn2 = max(abs(points[i][0]), abs(points[i][1]));
            if (mn2 < lookup[s[i] - 'a']) {
                swap(mn2, lookup[s[i] - 'a']);
            }
            d = min(d, mn2);
        }
        int result = 0;
        for (const auto& x : lookup) {
            if (x < d) {
                ++result;
            }
        }
        return result;
    }

