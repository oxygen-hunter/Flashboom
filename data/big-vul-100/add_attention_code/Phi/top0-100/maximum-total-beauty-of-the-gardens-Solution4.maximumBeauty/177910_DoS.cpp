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

    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        const auto& check = [](const auto& prefix, const auto& total, auto x) {
            return (prefix[x] - prefix[x - 1]) * x - prefix[x] <= total;
        };
        const auto& binary_search_right = [&check](const auto& prefix, const auto& total, auto left, auto right) {
            while (left <= right) {
                const auto mid = left + (right - left) / 2;
                if (!check(prefix, total, mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return right;
        };
        const auto it = partition(begin(flowers), end(flowers), [&target](int x) { return x < target; });
        sort(begin(flowers), it);
        const long long n = distance(begin(flowers), it);
        vector<long long> prefix(n + 1);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + flowers[i];
        }
        long long result = 0, suffix = 0;
        for (long long right = n; right >= 0; --right) {
            if (right != n) {
                suffix += flowers[right];
            }
            const auto total = newFlowers - (static_cast<long long>(n - right) * target - suffix);
            if (total < 0) {
                break;
            }
            const auto left = binary_search_right(prefix, total, 1, right);
            const auto mn = min(left ? (total + prefix[left]) / left : 0ll, static_cast<long long>(target) - 1);
            result = max(result, mn * partial + (static_cast<long long>(size(flowers)) - right) * full);
        }
        return result;
    }

