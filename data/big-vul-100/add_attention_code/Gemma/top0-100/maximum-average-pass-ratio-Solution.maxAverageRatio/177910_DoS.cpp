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


    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        static const auto& profit = [](double a, double b) {
            return (a + 1) / (b + 1) - a / b;
        };

        vector<tuple<double, int, int>> max_heap;
        for (const auto& c : classes) {
            max_heap.emplace_back(profit(c[0], c[1]), c[0], c[1]);
        }
        make_heap(begin(max_heap), end(max_heap));
        for (; extraStudents > 0; --extraStudents) {
            auto [_, a, b] = max_heap.front();
            ++a, ++b;
            pop_heap(begin(max_heap), end(max_heap)); max_heap.pop_back();
            max_heap.emplace_back(profit(a, b), a, b); push_heap(begin(max_heap), end(max_heap));
        }
        return accumulate(cbegin(max_heap), cend(max_heap), 0.0,
                          [](const auto& total, const auto& x) {
                              return total + float(get<1>(x)) / get<2>(x);
                          }) / size(classes);
    }


