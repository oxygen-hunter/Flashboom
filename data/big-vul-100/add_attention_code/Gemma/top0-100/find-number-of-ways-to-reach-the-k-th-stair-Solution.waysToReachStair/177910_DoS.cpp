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


    int waysToReachStair(int k) {
        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };

        const auto& ceil_log2_x = [&](int x) {
            return bit_length(x - 1);
        };
    
        int l = ceil_log2_x(k);
        for (; (1ll << l) - k <= l + 1; ++l);
        vector<__int128> fact(l + 1, 1);
        for (int i = 0; i + 1 < size(fact); ++i) {
            fact[i + 1] = fact[i] * (i + 1);
        }
        const auto& nCr = [&](int n, int r) {
            if (!(0 <= r && r <= n)) {
                return static_cast<__int128>(0);
            }
            return fact[n] / fact[r] / fact[n - r];
        };

        int result = 0;
        for (int i = 0; i < l; ++i) {
            result += nCr(i + 1, (1 << i) - k);
        }
        return result;
    }


