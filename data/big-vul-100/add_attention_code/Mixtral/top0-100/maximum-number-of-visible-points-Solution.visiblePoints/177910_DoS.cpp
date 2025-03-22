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

    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        static const double PI = atan2(0, -1);

        vector<double> arr;
        int extra = 0;
        for (const auto& p : points) {
            if (p == location) {
                ++extra;
                continue;
            }
            arr.emplace_back(atan2(p[1] - location[1], p[0] - location[0]));
        }
        sort(begin(arr), end(arr));
        const int n = size(arr);
        for (int i = 0; i < n; ++i) {  // make it circular
            arr.emplace_back(arr[i] + 2.0 * PI);
        }
        const double d = 2.0 * PI * (angle / 360.0);
        int result = 0;
        for (int left = 0, right = 0; right < size(arr); ++right) {
            while (arr[right] - arr[left] > d) {
                ++left;
            }
            result = max(result, right - left + 1);
        }
        return result + extra;
    }

