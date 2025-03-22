ztype(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    ref tnref;
    int code = array_get(imemory, op, (long)r_btype(op - 1), &tnref);

    if (code < 0)
        return code;
    if (!r_has_type(&tnref, t_name)) {
         /* Must be either a stack underflow or a t_[a]struct. */
         check_op(2);
         {                       /* Get the type name from the structure. */
            if (op[-1].value.pstruct != 0x00) {
             const char *sname =
                 gs_struct_type_name_string(gs_object_type(imemory,
                                                           op[-1].value.pstruct));
            int code = name_ref(imemory, (const byte *)sname, strlen(sname),
                                (ref *) (op - 1), 0);

            if (code < 0)
                return code;
            } else
                return_error(gs_error_stackunderflow);
        }
        r_set_attrs(op - 1, a_executable);
    } else {
        ref_assign(op - 1, &tnref);
    }
    pop(1);
    return 0;
}

    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        vector<vector<int>> adj(size(cost));
        for (const auto& e : edges) {
            adj[e[0]].emplace_back(e[1]);
            adj[e[1]].emplace_back(e[0]);
        }
        vector<long long> result(size(cost));
        const auto& iter_dfs = [&]() {
            vector<long long> result(size(cost));
            using RET = vector<int64_t>;
            RET ret = {cost[0]};
            vector<tuple<int, int, int, int, shared_ptr<RET>, RET *>> stk = {{1, 0, -1, -1, nullptr, &ret}};
            while (!stk.empty()) {
                const auto [step, u, p, i, new_ret, ret] = stk.back(); stk.pop_back();
                if (step == 1) {
                    stk.emplace_back(4, u, -1, -1, nullptr, ret);
                    stk.emplace_back(2, u, p, 0, nullptr, ret);
                } else if (step == 2) {
                    if (i == size(adj[u])) {
                        continue;
                    }
                    const auto& v = adj[u][i];
                    stk.emplace_back(2, u, p, i + 1, new_ret, ret);
                    if (v == p) {
                        continue;
                    }
                    const auto& new_ret = make_shared<RET>(RET{cost[v]});
                    stk.emplace_back(3, -1, -1, -1, new_ret, ret);
                    stk.emplace_back(1, v, u, -1, nullptr, new_ret.get());
                } else if (step == 3) {
                    for (const auto& c : *new_ret) {
                        ret->emplace_back(c);
                    }
                    sort(begin(*ret), end(*ret));
                    if (size(*ret) > 5) {
                        ret->assign({(*ret)[0], (*ret)[1], (*ret)[size(*ret) - 3], (*ret)[size(*ret) - 2], (*ret)[size(*ret) - 1]});
                    }
                } else if (step == 4) {
                    result[u] = size(*ret) < 3 ? 1 : max({(*ret)[0] * (*ret)[1] * (*ret)[size(*ret) - 1], (*ret)[size(*ret) - 3] * (*ret)[size(*ret) - 2] * (*ret)[size(*ret) - 1], static_cast<int64_t>(0)});
                }
            }
            return result;
        };

        return iter_dfs();
    }

