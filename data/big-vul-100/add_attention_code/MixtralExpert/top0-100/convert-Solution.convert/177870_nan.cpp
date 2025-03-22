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


        string convert(string s, int nRows) {
            vector<string> row(nRows);
            string ans;
            int cnt = 0;

            if(nRows == 1)
                return s;

            for(auto c : s) {
                if(cnt < nRows) {
                    row[cnt].push_back(c);
                }
                else {
                    row[2 * nRows - 2 - cnt].push_back(c);
                }

                cnt = (cnt + 1) % (2 * nRows - 2);
            }

            for(auto s : row) {
                ans.append(s);
            }

            return ans;
        }


