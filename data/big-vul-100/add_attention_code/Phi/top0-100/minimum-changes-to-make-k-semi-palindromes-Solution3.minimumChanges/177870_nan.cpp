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

    int minimumChanges(string s, int k) {
        vector<vector<int>> divisors(size(s) + 1);
        for (int i = 1; i < size(divisors); ++i) {  // Time: O(nlogn), Space: O(nlogn)
            for (int j = i + i; j < size(divisors); j += i) {
                divisors[j].emplace_back(i);
            }
        }

        const auto& dist = [&](int left, int right, int d) {
            int result = 0;
            for (int i = 0; i < (right - left + 1) / 2; ++i) {
                if (s[left + i] != s[right - ((i / d + 1) * d - 1) + (i % d)]) {
                    ++result;
                }
            }
            return result;
        };

        const auto& min_dist = [&](int left, int right) {  // Time: O(nlogn)
            int result = size(s);
            for (const auto& d : divisors[right - left + 1]) {
                result = min(result, dist(left, right, d));
            }
            return result;
        };
            
        vector<vector<int>> dp(size(s) + 1, vector<int>(k + 1, size(s)));
        dp[0][0] = 0;
        for (int i = 0; i < size(s); ++i) {  // Time: O(n^2 * nlogn + n^2 * k), Space: O(n * k)
            for (int j = 0; j < i; ++j) {
                const int c = min_dist(j, i);
                for (int l = 0; l < k; ++l) {
                    dp[i + 1][l + 1] = min(dp[i + 1][l + 1], dp[j][l] + c);
                }
            }
        }
        return dp[size(s)][k];
    }

