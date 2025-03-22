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

    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        vector<tuple<int, bool, int>> events;
        for (int i = 0; i < size(times); ++i) {
            events.emplace_back(times[i][0], true, i);
            events.emplace_back(times[i][1], false, i);
        }
        sort(begin(events), end(events));

        unordered_map<int, int> lookup;
        priority_queue<int, vector<int>, greater<int>> min_heap;
        for (const auto& [_, arrival, i] : events) {
            if (!arrival) {
                min_heap.emplace(lookup[i]);
                lookup.erase(i);
                continue;
            }
            if (!empty(min_heap)) {
                lookup[i] = min_heap.top(); min_heap.pop();
            } else {
                lookup[i] = size(lookup);
            }
            if (i == targetFriend) {
                break;
            }
        }
        return lookup[targetFriend];
    }

