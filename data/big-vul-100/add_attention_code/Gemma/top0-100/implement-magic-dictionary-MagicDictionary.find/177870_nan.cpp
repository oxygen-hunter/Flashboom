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


    bool find(const string& word, TrieNode *curr, int i, bool mistakeAllowed) {
        if (i == word.length()) {
            return curr->isString && !mistakeAllowed; 
        }

        if (!curr->leaves.count(word[i])) {
            return mistakeAllowed ?
                       any_of(curr->leaves.begin(), curr->leaves.end(),
                              [&](const pair<char, TrieNode *>& kvp) { 
                                  return find(word, kvp.second, i + 1, false);
                               }) :
                       false;
        }
                    
        if (mistakeAllowed) {
            return find(word, curr->leaves[word[i]], i + 1, true) ||
                   any_of(curr->leaves.begin(), curr->leaves.end(),
                          [&](const pair<char, TrieNode *>& kvp) { 
                              return kvp.first != word[i] && find(word, kvp.second, i + 1, false);
                          });
        }
        return find(word, curr->leaves[word[i]], i + 1, false);
    }


