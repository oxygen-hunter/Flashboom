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


        int numDistinct(const string &S, const string &T) {
            vector<int> f(T.size() + 1);
            f[0] = 1; // f(0, 0) = 1, means S = "" and T = "", there is only one distinct subsequence, i.e. ""
            for (int i = 1; i <= S.size(); ++i) {
                for (int j = T.size(); j > 0; --j) {
                    // f(i, j) is composed of:
                    // f(i−1,j): not using S[i - 1] 
                    // f(i−1,j−1): using S[i - 1] if S[i - 1] == S[j - 1]
                    f[j] += (S[i - 1] == T[j - 1]) ? f[j - 1] : 0;
                }
            }
            return f[T.size()];
        }


