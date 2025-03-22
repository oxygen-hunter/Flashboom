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

    bool areSentencesSimilar(string sentence1, string sentence2) {
        if (size(sentence1) > size(sentence2)) {
            swap(sentence1, sentence2);
        }
        int count = 0;
        for (int step = 0; step < 2; ++step) {
            for (int i = 0; i <= size(sentence1); ++i) {
                char c1 = i != size(sentence1) ? sentence1[step == 0 ? i : size(sentence1) - 1 - i] : ' ';
                char c2 = i != size(sentence2) ? sentence2[step == 0 ? i : size(sentence2) - 1 - i] : ' ';
                if (c1 != c2) {
                    break;
                }
                if (c1 == ' ') {
                    ++count;
                }
            }
        }
        return count >= count_if(cbegin(sentence1), cend(sentence1),
                                 [](char x) { return x == ' '; }) + 1;
    }

