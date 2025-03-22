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


    vector<int> findPattern(vector<vector<int>>& board, vector<string>& pattern) {
        const auto& check = [&](int i, int j) {
            vector<int> lookup(26, -1);
            vector<bool> lookup2(10);
            for (int r = 0; r < size(pattern); ++r) {
                for (int c = 0; c < size(pattern[0]); ++c) {
                    const int y = board[i + r][j + c];
                    if (isdigit(pattern[r][c])) {
                        if (pattern[r][c] - '0' != y) {
                            return false;
                        }
                        continue;
                    }
                    const int x = pattern[r][c] - 'a';
                    if (lookup[x] == -1) {
                        if (lookup2[y]) {
                            return false;
                        }
                        lookup2[y] = true;
                        lookup[x] = y;
                        continue;
                    }
                    if (lookup[x] != y) {
                        return false;
                    }
                }
            }
            return true;
        };
    
        for (int i = 0; i + size(pattern) - 1 < size(board); ++i) {
            for (int j = 0; j + size(pattern[0]) - 1 < size(board[0]); ++j) {
                if (check(i, j)) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }


