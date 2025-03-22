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

    int stoneGameV(vector<int>& stoneValue) {
        const int n = stoneValue.size();
        vector<int> prefix(n + 1);
        partial_sum(cbegin(stoneValue), cend(stoneValue), begin(prefix) + 1);

        vector<vector<int>> mid(n, vector<int>(n));
        for (int l = 1; l <= n; ++l) {
            for (int i = 0; i <= n - l; ++i) {
                const int j = i + l - 1;
                int p = (l == 1) ? i : mid[i][j - 1];
                while (prefix[p] - prefix[i] < prefix[j + 1] - prefix[p]) {
                    ++p;  // Time: O(n^2) in total
                }
                mid[i][j] = p;
            }
        }
        
        vector<vector<int>> rmq(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            rmq[i][i] = stoneValue[i];
        }

        vector<vector<int>> dp(n, vector<int>(n));
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i <= n - l; ++i) {
                const int j = i + l - 1;
                const int p = mid[i][j];
                int max_score = 0;
                if (prefix[p] - prefix[i] == prefix[j + 1] - prefix[p]) {
                    max_score = max(rmq[i][p - 1], rmq[j][p]);
                } else {
                    if (i <= p - 2) {
                        max_score = max(max_score, rmq[i][p - 2]);
                    }
                    if (p <= j) {
                        max_score = max(max_score, rmq[j][p]);
                    }
                }
                dp[i][j] = max_score;
                rmq[i][j] = max(rmq[i][j - 1], (prefix[j + 1] - prefix[i]) + max_score);
                rmq[j][i] = max(rmq[j][i + 1], (prefix[j + 1] - prefix[i]) + max_score);
            }
        }
        return dp[0][n - 1];
    }

