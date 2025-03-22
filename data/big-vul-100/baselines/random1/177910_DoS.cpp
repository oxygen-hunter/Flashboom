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


    int countTriplets(vector<int>& arr) {
        unordered_map<int, pair<int, int>> count_sum;
        count_sum[0] = {1, 0};
        int result = 0;
        for (int i = 0, prefix = 0; i < arr.size(); ++i) {
            prefix ^= arr[i];
            auto& [c, t] = count_sum[prefix];
            result += c * i - t;
            ++c, t += i + 1;
        }
        return result;
    }


