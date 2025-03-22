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


    vector<int> pathsWithMaxScore(vector<string>& board) {
        static const int MOD = 1e9 + 7;
        static const vector<pair<int, int>> directions{{1, 0}, {0, 1}, {1, 1}};
        
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(board[0].size() + 1, vector<int>(2)));
        dp[(board.size() - 1) % 2][board[0].size() - 1] = {0, 1};
        for (int r = board.size() - 1; r >= 0; --r) {
            for (int c = board[0].size() - 1; c >= 0; --c) {
                if (board[r][c] == 'S' || board[r][c] == 'X') {
                    continue;
                }
                dp[r % 2][c] = {0, 0};
                for (const auto& [dr, dc] : directions) {
                    if (dp[r % 2][c][0] < dp[(r + dr) % 2][c + dc][0]) {
                        dp[r % 2][c] = dp[(r + dr) % 2][c + dc];
                    } else if (dp[r % 2][c][0] == dp[(r + dr) % 2][c + dc][0]) {
                        dp[r % 2][c][1] = (dp[r % 2][c][1]+dp[(r + dr) % 2][c + dc][1]) % MOD;
                    }
                }
                if (dp[r % 2][c][1] && board[r][c] != 'E') {
                    dp[r % 2][c][0] += board[r][c] - '0';
                }
            }
        }
        return dp[0][0];
    }


