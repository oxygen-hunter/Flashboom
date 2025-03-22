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


    int maximumScore(vector<int>& nums, int k) {
        static const int MOD = 1e9 + 7;
        const auto& addmod = [&](uint32_t a, uint32_t b) {  // avoid overflow
            a %= MOD, b %= MOD;
            if (MOD - a <= b) {
                b -= MOD;  // relied on unsigned integer overflow in order to give the expected results
            }
            return a + b;
        };

        const auto& mulmod = [&](uint32_t a, uint32_t b)  {  // avoid overflow
            a %= MOD, b %= MOD;
            uint32_t result = 0;
            if (a < b) {
                swap(a, b);
            }
            while (b > 0)  { 
                if (b % 2 == 1) {
                    result = addmod(result, a);
                }
                a = addmod(a, a);
                b /= 2; 
            } 
            return result; 
        };

        const auto& powmod = [&](uint32_t a, uint32_t b) {
            a %= MOD;
            uint32_t result = 1;
            while (b) {
                if (b & 1) {
                    result = mulmod(result, a);
                }
                a = mulmod(a, a);
                b >>= 1;
            }
            return result;
        };
    
        const auto& linear_sieve_of_eratosthenes = [](int n) {  // Time: O(n), Space: O(n)
            vector<int> spf(n + 1, -1);
            vector<int> primes;
            for (int i = 2; i <= n; ++i) {
                if (spf[i] == -1) {
                    spf[i] = i;
                    primes.emplace_back(i);
                }
                for (const auto& p : primes) {
                    if (i * p > n || p > spf[i]) {
                        break;
                    }
                    spf[i * p] = p;
                }
            }
            return primes;
        };
    
        const auto& primes = linear_sieve_of_eratosthenes(sqrt(*max_element(cbegin(nums), cend(nums))));
        unordered_map<int, int> lookup;
        const auto& count_of_distinct_prime_factors = [&](int x) {
            const int y = x;
            if (!lookup.count(y)) {
                int cnt = 0;
                for (const auto& p : primes) {
                    if (p * p > x) {
                        break;
                    }
                    if (x % p != 0) {
                        continue;
                    }
                    ++cnt;
                    for (; x % p == 0; x /= p);
                }
                if (x != 1) {
                    ++cnt;
                }
                lookup[y] = cnt;
            }
            return lookup[y];
        };

        vector<int> scores;
        scores.reserve(size(nums));
        for (const auto& x : nums) {
            scores.emplace_back(count_of_distinct_prime_factors(x));
        }

        vector<int> stk = {-1};
        vector<int> left(size(scores), -1);
        for (int i = 0; i < size(scores); ++i) {
            while (stk.back() != -1 && scores[stk.back()] < scores[i]) {  // if multiple such elements exist, choose the one with the smallest index
                stk.pop_back();
            }
            left[i] = stk.back();
            stk.emplace_back(i);
        }
        stk = {static_cast<int>(size(scores))};
        vector<int> right(size(scores), -1);
        for (int i =  size(scores) - 1; i >= 0; --i) {
            while (stk.back() != size(scores) && scores[stk.back()] <= scores[i]) {
                stk.pop_back();
            }
            right[i] = stk.back();
            stk.emplace_back(i);
        }

        int result = 1;
        vector<pair<int, int>> pairs;
        pairs.reserve(size(nums));
        for (int i = 0; i < size(nums); ++i) {
            pairs.emplace_back(nums[i], i);
        }
        priority_queue<pair<int, int>> max_heap(cbegin(pairs), cend(pairs));
        while (!empty(max_heap)) {
            const auto [_, i] = max_heap.top(); max_heap.pop();
            const int c = min((i - left[i]) * (right[i] - i), k);
            result = mulmod(result, powmod(nums[i], c));
            k -= c;
            if (!k) {
                break;
            }
        }
        return result;
    }


