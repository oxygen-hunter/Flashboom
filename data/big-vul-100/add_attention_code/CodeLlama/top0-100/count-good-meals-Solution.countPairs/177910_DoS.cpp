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


    int countPairs(vector<int>& deliciousness) {
        static const int MOD = 1e9 + 7;

        static const auto& floor_log2_x = [](int x) {
            return 8 * sizeof(int) - __builtin_clz(x) - 1;
        };
        
        int max_pow = floor_log2_x(*max_element(cbegin(deliciousness),
                                                cend(deliciousness))) + 1;
        unordered_map<int, int> cnt;
        int result = 0;
        for (const auto& d : deliciousness) {
            int p = 1;
            for (int i = 0; i <= max_pow; ++i) {
                result = (result + cnt[p - d]) % MOD;
                p <<= 1;
            }
            ++cnt[d];
        }
        return result;
    }


