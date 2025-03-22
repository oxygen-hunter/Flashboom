int test_mod_exp(BIO *bp, BN_CTX *ctx)
{
    BIGNUM *a, *b, *c, *d, *e;
    int i;

    a = BN_new();
    b = BN_new();
    c = BN_new();
    d = BN_new();
    e = BN_new();

    BN_one(a);
    BN_one(b);
    BN_zero(c);
    if (BN_mod_exp(d, a, b, c, ctx)) {
        fprintf(stderr, "BN_mod_exp with zero modulus succeeded!\n");
        return 0;
    }

    BN_bntest_rand(c, 30, 0, 1); /* must be odd for montgomery */
    for (i = 0; i < num2; i++) {
        BN_bntest_rand(a, 20 + i * 5, 0, 0);
        BN_bntest_rand(b, 2 + i, 0, 0);

        if (!BN_mod_exp(d, a, b, c, ctx))
            return (0);

        if (bp != NULL) {
            if (!results) {
                BN_print(bp, a);
                BIO_puts(bp, " ^ ");
                BN_print(bp, b);
                BIO_puts(bp, " % ");
                BN_print(bp, c);
                BIO_puts(bp, " - ");
            }
            BN_print(bp, d);
            BIO_puts(bp, "\n");
        }
        BN_exp(e, a, b, ctx);
        BN_sub(e, e, d);
        BN_div(a, b, e, c, ctx);
        if (!BN_is_zero(b)) {
            fprintf(stderr, "Modulo exponentiation test failed!\n");
             return 0;
         }
     }
     BN_free(a);
     BN_free(b);
     BN_free(c);
    BN_zero(c);
    if (BN_mod_exp_mont_consttime(d, a, b, c, ctx, NULL)) {
        fprintf(stderr, "BN_mod_exp_mont_consttime with zero modulus "
                "succeeded\n");
        return 0;
    }

    BN_set_word(c, 16);
    if (BN_mod_exp_mont_consttime(d, a, b, c, ctx, NULL)) {
        fprintf(stderr, "BN_mod_exp_mont_consttime with even modulus "
                "succeeded\n");
        return 0;
    }

    BN_bntest_rand(c, 30, 0, 1); /* must be odd for montgomery */
    for (i = 0; i < num2; i++) {
        BN_bntest_rand(a, 20 + i * 5, 0, 0);
        BN_bntest_rand(b, 2 + i, 0, 0);

        if (!BN_mod_exp_mont_consttime(d, a, b, c, ctx, NULL))
            return (00);

        if (bp != NULL) {
            if (!results) {
                BN_print(bp, a);
                BIO_puts(bp, " ^ ");
                BN_print(bp, b);
                BIO_puts(bp, " % ");
                BN_print(bp, c);
                BIO_puts(bp, " - ");
            }
            BN_print(bp, d);
            BIO_puts(bp, "\n");
        }
        BN_exp(e, a, b, ctx);
        BN_sub(e, e, d);
        BN_div(a, b, e, c, ctx);
        if (!BN_is_zero(b)) {
            fprintf(stderr, "Modulo exponentiation test failed!\n");
            return 0;
        }
    }
    BN_free(a);
    BN_free(b);
    BN_free(c);
    BN_free(d);
    BN_free(e);
    return (1);
}


    int findCrossingTime(int n, int k, vector<vector<int>>& time) {
        vector<pair<int, int>> workers;
        for (int i = 0; i < k; ++i) {
            workers.emplace_back(time[i][0] + time[i][2], i);
        }
        priority_queue<pair<int, int>> left_bridge(cbegin(workers), cend(workers)), right_bridge;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> left_ware, right_ware;
        int curr = 0;
        while (n) {
            while (!empty(left_ware) && left_ware.top().first <= curr) {
                const auto [_, i] = left_ware.top(); left_ware.pop();
                left_bridge.emplace(time[i][0] + time[i][2], i);
            }
            while (!empty(right_ware) && right_ware.top().first <= curr) {
                const auto [_, i] = right_ware.top(); right_ware.pop();
                right_bridge.emplace(time[i][0] + time[i][2], i);
            }
            if (!empty(right_bridge)) {
                const auto [_, i] = right_bridge.top(); right_bridge.pop();
                curr += time[i][2];
                left_ware.emplace(curr + time[i][3], i);
                --n;
            } else if (!empty(left_bridge) && n - size(right_ware)) {
                const auto [_, i] = left_bridge.top(); left_bridge.pop();
                curr += time[i][0];
                right_ware.emplace(curr + time[i][1], i);
            } else {
                curr = min(!empty(left_ware) ? left_ware.top().first : numeric_limits<int>::max(),
                           !empty(right_ware) ? right_ware.top().first : numeric_limits<int>::max());
            }
        }
        return curr;
    }


