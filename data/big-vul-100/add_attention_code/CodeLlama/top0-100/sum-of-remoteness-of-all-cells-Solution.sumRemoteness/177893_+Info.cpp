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


    long long sumRemoteness(vector<vector<int>>& grid) {
        static const vector<pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        const auto& bfs = [&](int i, int j) {
            int64_t total = grid[i][j];
            int cnt = 1;
            grid[i][j] = -1;
            vector<pair<int64_t, int>> q = {{i, j}};
            while (!empty(q)) {
                vector<pair<int64_t, int>> new_q;
                for (const auto& [i, j] : q) {
                    for (const auto& [di, dj] : DIRECTIONS) {
                        int ni = i + di, nj = j + dj;
                        if (!(0 <= ni && ni < size(grid) &&
                              0 <= nj && nj < size(grid[0]) &&
                              grid[ni][nj] != -1)) {
                            continue;
                        }
                        total += grid[ni][nj];
                        ++cnt;
                        grid[ni][nj] = -1;
                        new_q.emplace_back(ni, nj);
                    }
                }
                q = move(new_q);
            }
            return pair(total, cnt);
        };
    
        vector<pair<int64_t, int>> groups;
        for (int i = 0; i < size(grid); ++i) {
            for (int j = 0; j < size(grid[0]); ++j) {
                if (grid[i][j] == -1) {
                    continue;
                }
                groups.emplace_back(bfs(i, j));
            }
        }
        int64_t total = 0;
        for (const auto& [t, _] : groups) {
            total += t;
        }
        int64_t result = 0;
        for (const auto& [t, c] : groups) {
            result += (total - t) * c;
        }
        return result;
    }


