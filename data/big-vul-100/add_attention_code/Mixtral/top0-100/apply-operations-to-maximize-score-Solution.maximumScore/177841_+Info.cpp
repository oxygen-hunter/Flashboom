_PUBLIC_ char *strupper_talloc_n_handle(struct smb_iconv_handle *iconv_handle,
					TALLOC_CTX *ctx, const char *src, size_t n)
{
	size_t size=0;
	char *dest;

	if (!src) {
		return NULL;
	}

	/* this takes advantage of the fact that upper/lower can't
	   change the length of a character by more than 1 byte */
	dest = talloc_array(ctx, char, 2*(n+1));
	if (dest == NULL) {
                return NULL;
        }
 
       while (n-- && *src) {
                size_t c_size;
                codepoint_t c = next_codepoint_handle_ext(iconv_handle, src, n,
                                                          CH_UNIX, &c_size);
                src += c_size;
 
                c = toupper_m(c);
		if (c_size == -1) {
			talloc_free(dest);
			return NULL;
		}
		size += c_size;
	}

	dest[size] = 0;

	/* trim it so talloc_append_string() works */
	dest = talloc_realloc(ctx, dest, char, size+1);

	talloc_set_name_const(dest, dest);

	return dest;
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

