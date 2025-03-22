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

    int numWays(string s) {
        static const int MOD = 1e9 + 7;
        int ones = count_if(cbegin(s), cend(s),
                            [](const auto& x) {
                                return x == '1';
                            });
        if (ones % 3) {
            return 0;
        }
        ones /= 3;
        if (ones == 0) {
            return static_cast<int64_t>(s.length() - 1) * (s.length() - 2) / 2 % MOD;
        }
        int count = 0, left = 0, right = 0;
        for (const auto& c : s) {
            if (c == '1') {
                ++count;
            }
            if (count == ones) {
                ++left;
            } else if (count == 2 * ones) {
                ++right;
            }
        }
        return static_cast<int64_t>(left) * right % MOD;
    }

