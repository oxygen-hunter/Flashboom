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

    bool isPossible(vector<int>& target) {
        // (1) x + remain = y
        // (2) y + remain = total
        // (1) - (2) => x - y = y - total
        //           => x = 2*y - total
        auto total = accumulate(cbegin(target), cend(target), 0ll);
        priority_queue<int> max_heap(cbegin(target), cend(target));
        while (total != target.size()) {
            const auto y = max_heap.top(); max_heap.pop();
            const auto& remain = total - y;
            auto x = y - remain;
            if (x <= 0) {
                return false;
            }
            if (x > remain) {  // for case [1, 1000000000]
                x = x % remain + remain;
            }
            max_heap.emplace(x);
            total = x + remain;
        }
        return true;
    }

