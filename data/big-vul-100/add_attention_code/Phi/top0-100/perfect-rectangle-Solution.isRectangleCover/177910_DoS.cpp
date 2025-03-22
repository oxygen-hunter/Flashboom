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

    bool isRectangleCover(vector<vector<int>>& rectangles) {
        enum Location {L = 0, B = 1, R = 2, T = 3};
        int left = numeric_limits<int>::max(), bottom = numeric_limits<int>::max(),
            right = numeric_limits<int>::min(), top = numeric_limits<int>::min();
        for (const auto& rect : rectangles) {
            left = min(left, rect[L]);
            bottom = min(bottom, rect[B]);
            right = max(right, rect[R]);
            top = max(top, rect[T]);
        }

        using P = pair<pair<int, int>, int>;
        enum Corner {LB = 1, RB = 2, LT = 4, RT = 8};
        unordered_map<int, unordered_map<int, int>> corner_count;
        vector<P> corners{{{L, B}, LB}, {{R, B}, RB}, {{L, T}, LT}, {{R, T}, RT}};
        for (const auto& rect : rectangles) {
            for (const auto& corner : corners) {
                const auto x = rect[corner.first.first];
                const auto y = rect[corner.first.second];
                if (corner_count[x][y] & corner.second) {
                    return false;
                }
                corner_count[x][y] |= corner.second;
            }
        }

        bitset<16> is_valid;
        is_valid[LB | RB] = is_valid[LB | LT] = is_valid[RB | RT] = is_valid[LT | RT] = is_valid[LB | RB | LT | RT] = true;
        for (auto itx = corner_count.cbegin(); itx != corner_count.cend(); ++itx) {
            const auto x = itx->first;
            for (auto ity = itx->second.cbegin(); ity != itx->second.cend(); ++ity) {
                const auto y = ity->first;
                const auto mask = ity->second;
                if ((left < x && x < right) || (bottom < y && y < top)) {
                    if (!is_valid[mask]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

