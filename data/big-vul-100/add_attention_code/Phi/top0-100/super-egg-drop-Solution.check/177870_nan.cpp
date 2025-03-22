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

    bool check(int n, int K, int N) {
        // let f(n, K) be the max number of floors could be solved by n moves and K eggs,
        // we want to do binary search to find min of n, s.t. f(n, K) >= N,
        // if we use one move to drop egg with X floors
        // 1. if it breaks, we can search new X in the range [X+1, X+f(n-1, K-1)]
        // 2. if it doesn't break, we can search new X in the range [X-f(n-1, K), X-1]
        // => f(n, K) = (X+f(n-1, K-1))-(X-f(n-1, K))+1 = f(n-1, K-1)+f(n-1, K)+1
        // => (1) f(n, K)   = f(n-1, K)  +1+f(n-1, K-1)
        //    (2) f(n, K-1) = f(n-1, K-1)+1+f(n-1, K-2)
        // let g(n, K) = f(n, K)-f(n, K-1), and we subtract (1) by (2)
        // => g(n, K) = g(n-1, K)+g(n-1, K-1), obviously, it is binomial coefficient
	    // => C(n, K) = g(n, K) = f(n, K)-f(n, K-1),
        //    which also implies if we have one more egg with n moves and x-1 egges, we can have more C(n, x) floors solvable
        // => f(n, K) = C(n, K)+f(n, K-1) = C(n, K) + C(n, K-1) + ... + C(n, 1) + f(n, 0) = sum(C(n, k) for k in [1, K])
        // => all we have to do is to check sum(C(n, k) for k in [1, K]) >= N,
        //    if true, there must exist a 1-to-1 mapping from each F in [1, N] to each sucess and failure sequence of every C(n, k) combinations for k in [1, K]
        int total = 0, c = 1;
        for (int k = 1; k <= K; ++k) {
            c *= n - k + 1;
            c /= k;
            total += c;
            if (total >= N) {
                return true;
            }
        }
        return false;
    }

