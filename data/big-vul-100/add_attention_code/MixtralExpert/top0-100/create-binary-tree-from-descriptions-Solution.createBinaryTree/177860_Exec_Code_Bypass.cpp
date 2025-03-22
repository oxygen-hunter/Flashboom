zrestore(i_ctx_t *i_ctx_p)
 {
     os_ptr op = osp;
    alloc_save_t *asave;
    bool last;
    vm_save_t *vmsave;
    int code = restore_check_operand(op, &asave, idmemory);
 
     if (code < 0)
         return code;
     if_debug2m('u', imemory, "[u]vmrestore 0x%lx, id = %lu\n",
               (ulong) alloc_save_client_data(asave),
                (ulong) op->value.saveid);
     if (I_VALIDATE_BEFORE_RESTORE)
         ivalidate_clean_spaces(i_ctx_p);
        ivalidate_clean_spaces(i_ctx_p);
    /* Check the contents of the stacks. */
     {
         int code;
 
        if ((code = restore_check_stack(i_ctx_p, &o_stack, asave, false)) < 0 ||
            (code = restore_check_stack(i_ctx_p, &e_stack, asave, true)) < 0 ||
            (code = restore_check_stack(i_ctx_p, &d_stack, asave, false)) < 0
             ) {
             osp++;
             return code;
         }
     }
     /* Reset l_new in all stack entries if the new save level is zero. */
     /* Also do some special fixing on the e-stack. */
     restore_fix_stack(i_ctx_p, &o_stack, asave, false);
    }


    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode *> nodes;
        unordered_set<int> children;
        for (const auto& d : descriptions) {
            if (!nodes.count(d[0])) {
                nodes[d[0]] = new TreeNode(d[0]);
            }
            if (!nodes.count(d[1])) {
                nodes[d[1]] = new TreeNode(d[1]);
            }
            if (d[2]) {
                nodes[d[0]]->left = nodes[d[1]];
            } else {
                nodes[d[0]]->right = nodes[d[1]];
            }
            children.emplace(d[1]);
        }
        for (const auto& [k, v] : nodes) {
            if (!children.count(k)) {
                return v;
            }
        }
        return nullptr;
    }


