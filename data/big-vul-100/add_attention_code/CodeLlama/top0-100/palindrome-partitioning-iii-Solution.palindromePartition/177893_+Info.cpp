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


    int palindromePartition(string s, int k) {
        // dp1[i][j]: minimum number of changes to make s[i, j] palindrome
        vector<vector<int>> dp1(s.length(), vector<int>(s.length()));
        for (int l = 1; l <= s.length(); ++l) {
            for (int i = 0; i + l <= s.length(); ++i) {
                int j = i + l - 1;
                if (i == j - 1) {
                    dp1[i][j] = s[i] == s[j] ? 0 : 1;
                }  else if (i != j) {
                    dp1[i][j] = s[i] == s[j] ? dp1[i + 1][j - 1] : dp1[i + 1][j - 1] + 1;
                }
            }
        }
        // dp2[d][i]: minimum number of changes to divide s[0, i] into d palindromes
        vector<vector<int>> dp2(2, vector<int>(s.length(), numeric_limits<int>::max()));
        dp2[1] = dp1[0];
        for (int d = 2; d <= k; ++d) {
            dp2[d % 2] = vector<int>(s.length(), numeric_limits<int>::max());
            for (int i = d - 1; i < s.length(); ++i) {
                for (int j = d - 2; j < i; ++j) {
                    dp2[d % 2][i] = min(dp2[d % 2][i], dp2[(d - 1) % 2][j] + dp1[j + 1][i]);
                }
            }
        }
        return dp2[k % 2][s.length() - 1];
    }


