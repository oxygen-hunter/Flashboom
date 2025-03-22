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


    string countOfAtoms(string formula) {
        stack<map<string, int>> stk;
        stk.emplace();
        int submatches[] = { 1, 2, 3, 4, 5 };
        const auto e = regex("([A-Z][a-z]*)(\\d*)|(\\()|(\\))(\\d*)");
        for (regex_token_iterator<string::iterator> it(formula.begin(), formula.end(), e, submatches), end;
             it != end;) {
            const auto& name = (it++)->str();
            const auto& m1 = (it++)->str();
            const auto& left_open = (it++)->str();
            const auto& right_open = (it++)->str();
            const auto& m2 = (it++)->str();
            if (!name.empty()) {
                stk.top()[name] += stoi(!m1.empty() ? m1 : "1");
            }
            if (!left_open.empty()) {
                stk.emplace();
            }
            if (!right_open.empty()) {
                const auto top = move(stk.top()); stk.pop();
                for (const auto& kvp: top) {
                    stk.top()[kvp.first] += kvp.second * stoi(!m2.empty() ? m2 : "1");
                }
            }
        }
        string result;
        for (const auto& kvp : stk.top()) {
            result += kvp.first;
            if (kvp.second > 1) {
                result += to_string(kvp.second);
            }
        }
        return result;
    }


