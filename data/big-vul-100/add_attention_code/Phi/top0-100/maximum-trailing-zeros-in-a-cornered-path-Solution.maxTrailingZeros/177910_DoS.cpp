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

    int maxTrailingZeros(vector<vector<int>>& grid) {
        const auto& factor = [](int x) {
            static const array<int, 2> primes = {2, 5};
            array<int, 2> cnt = {0, 0};
            for (int i = 0; i < size(primes); ++i) {
                while (x && x % primes[i] == 0) {
                    x /= primes[i];
                    ++cnt[i];
                }
            }
            return cnt;
        };
        const auto& add = [](const auto& a, const auto& b) {
            return array<int, 2>{a[0] + b[0], a[1] + b[1]};
        };
        const auto& sub = [](const auto& a, const auto& b) {
            return array<int, 2>{a[0] - b[0], a[1] - b[1]};
        };
        const auto& count = [](const auto& a) {
            return min(a[0], a[1]);
        };

        vector<vector<array<int, 2>>> left(size(grid), vector<array<int, 2>>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            left[i][0] = factor(grid[i][0]);
            for (int j = 1; j < size(grid[0]); ++j) {
                left[i][j] = add(left[i][j - 1], factor(grid[i][j]));
            }
        }
        int result = 0;
        for (int j = 0; j < size(grid[0]); ++j) {
            array<int, 2> total = {0, 0};
            for (int i = 0; i < size(grid); ++i) {
                total = add(total, factor(grid[i][j]));
            }
            array<int, 2> up = {0, 0};
            for (int i = 0; i < size(grid); ++i) {
                const auto& right = j ? sub(left[i].back(), left[i][j - 1]) : left[i].back();
                result = max({result, count(add(left[i][j], up)), count(add(right, up))});
                up = add(up, factor(grid[i][j]));
                const auto& down = sub(total, up);
                result = max({result, count(add(left[i][j], down)), count(add(right, down))});
            }
        }
        return result;
    }

