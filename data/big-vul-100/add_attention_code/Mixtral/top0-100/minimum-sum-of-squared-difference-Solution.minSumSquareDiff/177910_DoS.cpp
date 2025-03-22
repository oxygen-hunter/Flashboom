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

    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        vector<int64_t> diffs(size(nums1));
        for (int i = 0; i < size(diffs); ++i) {
            diffs[i] = abs(nums1[i] - nums2[i]);
        }
        sort(rbegin(diffs), rend(diffs));
        int64_t k = min(static_cast<int64_t>(k1) + k2, accumulate(cbegin(diffs), cend(diffs), static_cast<int64_t>(0)));
        const auto& check = [&](int x) {
            return accumulate(cbegin(diffs), cend(diffs), 0ll,
                              [&](const auto& total, const auto& d) {
                                  return total + max(d - x, static_cast<int64_t>(0));
                              }) <= k;
        };
        int64_t left = 0, right = diffs[0];
        while (left <= right) {
            const int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        k -= accumulate(cbegin(diffs), cend(diffs), 0ll,
                        [&](const auto& total, const auto& d) {
                            return total + max(d - left, static_cast<int64_t>(0));
                        });
        for (int i = 0; i < size(diffs); ++i) {
            diffs[i] = min(diffs[i], left) - int(i < k);
        }
        return accumulate(cbegin(diffs), cend(diffs), 0ll,
                          [](const auto& total, const auto& d) {
                              return total + d * d;
                          });
    }

