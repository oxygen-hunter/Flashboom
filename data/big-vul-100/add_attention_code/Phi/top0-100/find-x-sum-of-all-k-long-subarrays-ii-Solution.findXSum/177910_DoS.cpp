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

    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        using ordered_set = tree<pair<int, int64_t>, null_type, greater<pair<int, int64_t>>, rb_tree_tag, tree_order_statistics_node_update>;
        ordered_set os;
        unordered_map<int, int64_t> cnt;
        const auto& update = [&](int v, int64_t d, int64_t curr) {
            if (d == 1) {
                os.insert({cnt[v], v});
            }
            if (os.order_of_key(pair(cnt[v], v)) < x) {
                curr += d * cnt[v] * v;
                if (x < size(os)) {
                    const auto [nc, nv] = *(os.find_by_order(x));
                    curr -= d * nc * nv;
                }
            }
            if (d != 1) {
                os.erase(pair(cnt[v], v));
            }
            return curr;
        };

        vector<long long> result;
        for (int64_t i = 0, curr = 0; i < size(nums); ++i) {
            if (cnt.count(nums[i])) {
                curr = update(nums[i], -1, curr);
            }
            ++cnt[nums[i]];
            curr = update(nums[i], +1, curr);
            if (i < k - 1) {
                continue;
            }
            result.emplace_back(curr);
            curr = update(nums[i - (k - 1)], -1, curr);
            --cnt[nums[i - (k - 1)]];
            if (cnt[nums[i - (k - 1)]]) {
                curr = update(nums[i - (k - 1)], +1, curr);
            } else {
                cnt.erase(nums[i - (k - 1)]);
            }
        }
        return result;
    }

