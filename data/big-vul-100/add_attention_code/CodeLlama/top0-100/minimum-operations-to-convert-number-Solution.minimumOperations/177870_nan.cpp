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


