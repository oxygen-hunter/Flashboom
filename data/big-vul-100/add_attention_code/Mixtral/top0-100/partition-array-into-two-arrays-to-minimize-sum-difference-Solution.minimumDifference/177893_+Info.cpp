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

    int minimumDifference(vector<int>& nums) {
        vector<int> left, right; 
        for (int i = 0; i < size(nums); ++i) {
            if (i < size(nums) / 2) {
                left.emplace_back(nums[i]); 
            } else {
                right.emplace_back(nums[i]); 
            }
        }
        const auto& total1 = accumulate(cbegin(left), cend(left), 0);
        const auto& total2 = accumulate(cbegin(right), cend(right), 0);
        const int bound = (1 << size(left));
        unordered_map<int, vector<int>> sums;
        for (int mask = 0; mask < bound; ++mask) {
            int total = 0, bit = 1;
            for (const auto& x : left) {
                if (mask & bit) {
                    total += x; 
                }
                bit <<= 1;
            }
            sums[__builtin_popcount(mask)].emplace_back(2 * total - total1); 
        }
        for (auto& [_, v] : sums) {
            sort(begin(v), end(v));
        }
        int result = numeric_limits<int>::max();
        for (int mask = 0; mask < bound; ++mask) {
            int total = 0, bit = 1;
            for (const auto& x : right) {
                if (mask & bit) {
                    total += x; 
                }
                bit <<= 1;
            }
            const int k = size(right) - __builtin_popcount(mask);
            const int diff = 2 * total - total2; 
            const auto cit = lower_bound(cbegin(sums[k]), cend(sums[k]), -diff); 
            if (cit != cend(sums[k])) {
                result = min(result, abs(*cit + diff)); 
            }
            if (cit != cbegin(sums[k])) {
                result = min(result, abs(*prev(cit) + diff));    
            }
        }
        return result; 
    }

