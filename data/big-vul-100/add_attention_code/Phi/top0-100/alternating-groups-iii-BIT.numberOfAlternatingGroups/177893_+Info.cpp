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

    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        const int n = size(colors);
        set<int> bst;
        BIT bit1(n + 1), bit2(n + 1);
        const auto& update = [&](int i, int d) {
            if (d == +1) {
                bst.emplace(i);
                if (size(bst) == 1) {
                    bit1.add(n, +1);
                    bit2.add(n, +n);
                }
            }
            auto curr = bst.find(i);
            auto prv = prev(curr != begin(bst) ? curr : end(bst));
            auto nxt = next(curr);
            if (nxt == end(bst)) {
                nxt = begin(bst);
            }
            if (size(bst) != 1) {
                int l = ((*nxt) - (*prv) + (n - 1)) % n + 1;
                bit1.add(l, d * -1);
                bit2.add(l, d * -l);
                l = ((*curr) - (*prv) + n) % n;
                bit1.add(l, d * +1);
                bit2.add(l, d * +l);
                l = ((*nxt) - (*curr) + n) % n;
                bit1.add(l, d * +1);
                bit2.add(l, d * +l);
            }
            if (d == -1) {
                if (size(bst) == 1) {
                    bit1.add(n, -1);
                    bit2.add(n, -n);
                }
                bst.erase(curr);
            }
        };

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (colors[i] == colors[(i + 1) % n]) {
                update(i, +1);
            }
        }
        for (const auto &q : queries) {
            if (q[0] == 1) {
                const int l = q[1];
                result.emplace_back(!empty(bst) ? (bit2.query(n) - bit2.query(l - 1)) - 
                                                  (l - 1) * (bit1.query(n) - bit1.query(l - 1)) : n);
                continue;
            }
            const int i = q[1];
            if (colors[i] == q[2]) {
                continue;
            }
            colors[i] = q[2];
            update((i - 1 + n) % n, colors[i] == colors[(i - 1 + n) % n] ? +1 : -1);
            update(i, colors[i] == colors[(i + 1) % n] ? +1 : -1);
        }
        return result;
    }

