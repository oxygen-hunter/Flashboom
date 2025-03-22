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

    bool isValidPalindrome(string s, int k) {
        if (s == string(s.rbegin(), s.rend())) {  // optional, to optimize special case
            return true;
        }
        
        vector<vector<int>> dp(2, vector<int>(s.size(), 1));
        for (int i = s.length() - 2; i >= 0; --i) {
            for (int j = i + 1; j < s.length(); ++j) {
                if (s[i] == s[j]) {
                    dp[i % 2][j] = (i + 1 <= j - 1) ? 2 + dp[(i + 1) % 2][j - 1] : 2;
                } else {
                    dp[i % 2][j] = max(dp[(i + 1) % 2][j], dp[i % 2][j - 1]);
                }
            }
        }
        return s.length() <= k +dp[0][s.length() - 1];
    }

