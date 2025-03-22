token_continue(i_ctx_t *i_ctx_p, scanner_state * pstate, bool save)
{
    os_ptr op = osp;
     int code;
     ref token;
 
     /* Note that gs_scan_token may change osp! */
     pop(1);                     /* remove the file or scanner state */
 again:
            gs_scanner_error_object(i_ctx_p, pstate, &i_ctx_p->error_object);
            break;
        case scan_BOS:
            code = 0;
        case 0:         /* read a token */
            push(2);
            ref_assign(op - 1, &token);
            make_true(op);
            break;
        case scan_EOF:          /* no tokens */
            push(1);
            make_false(op);
            code = 0;
            break;
        case scan_Refill:       /* need more data */
            code = gs_scan_handle_refill(i_ctx_p, pstate, save,
                                      ztoken_continue);
            switch (code) {
                case 0: /* state is not copied to the heap */
                    goto again;
                case o_push_estack:
                    return code;
            }
            break;              /* error */
    }


    void addNum(int num) {
        // Balance smaller half and larger half.
        if (max_bst_.empty() || num > *max_bst_.cbegin()) {
            min_bst_.emplace(num);
            if (min_bst_.size() > max_bst_.size() + 1) {
                max_bst_.emplace(*min_bst_.cbegin());
                min_bst_.erase(min_bst_.cbegin());
            }
        } else {
            max_bst_.emplace(num);
            if (max_bst_.size() > min_bst_.size()) {
                min_bst_.emplace(*max_bst_.cbegin());
                max_bst_.erase(max_bst_.cbegin());
            }
        }
    }


