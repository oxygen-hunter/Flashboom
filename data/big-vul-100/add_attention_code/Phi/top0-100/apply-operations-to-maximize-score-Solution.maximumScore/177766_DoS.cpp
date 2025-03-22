static bool ldap_push_filter(struct asn1_data *data, struct ldb_parse_tree *tree)
{
	int i;

        switch (tree->operation) {
        case LDB_OP_AND:
        case LDB_OP_OR:
               asn1_push_tag(data, ASN1_CONTEXT(tree->operation==LDB_OP_AND?0:1));
                for (i=0; i<tree->u.list.num_elements; i++) {
                        if (!ldap_push_filter(data, tree->u.list.elements[i])) {
                                return false;
                        }
                }
               asn1_pop_tag(data);
                break;
 
        case LDB_OP_NOT:
               asn1_push_tag(data, ASN1_CONTEXT(2));
                if (!ldap_push_filter(data, tree->u.isnot.child)) {
                        return false;
                }
               asn1_pop_tag(data);
                break;
 
        case LDB_OP_EQUALITY:
                /* equality test */
               asn1_push_tag(data, ASN1_CONTEXT(3));
               asn1_write_OctetString(data, tree->u.equality.attr,
                                     strlen(tree->u.equality.attr));
               asn1_write_OctetString(data, tree->u.equality.value.data,
                                     tree->u.equality.value.length);
               asn1_pop_tag(data);
                break;
 
        case LDB_OP_SUBSTRING:
		/*
		  SubstringFilter ::= SEQUENCE {
			  type            AttributeDescription,
			  -- at least one must be present
			  substrings      SEQUENCE OF CHOICE {
				  initial [0] LDAPString,
                                  any     [1] LDAPString,
                                  final   [2] LDAPString } }
                */
               asn1_push_tag(data, ASN1_CONTEXT(4));
               asn1_write_OctetString(data, tree->u.substring.attr, strlen(tree->u.substring.attr));
               asn1_push_tag(data, ASN1_SEQUENCE(0));
 
                if (tree->u.substring.chunks && tree->u.substring.chunks[0]) {
                        i = 0;
                        if (!tree->u.substring.start_with_wildcard) {
                               asn1_push_tag(data, ASN1_CONTEXT_SIMPLE(0));
                               asn1_write_DATA_BLOB_LDAPString(data, tree->u.substring.chunks[i]);
                               asn1_pop_tag(data);
                                i++;
                        }
                        while (tree->u.substring.chunks[i]) {
				int ctx;

				if (( ! tree->u.substring.chunks[i + 1]) &&
				    (tree->u.substring.end_with_wildcard == 0)) {
					ctx = 2;
                                } else {
                                        ctx = 1;
                                }
                               asn1_push_tag(data, ASN1_CONTEXT_SIMPLE(ctx));
                               asn1_write_DATA_BLOB_LDAPString(data, tree->u.substring.chunks[i]);
                               asn1_pop_tag(data);
                                i++;
                        }
                }
               asn1_pop_tag(data);
               asn1_pop_tag(data);
                break;
 
        case LDB_OP_GREATER:
                /* greaterOrEqual test */
               asn1_push_tag(data, ASN1_CONTEXT(5));
               asn1_write_OctetString(data, tree->u.comparison.attr,
                                     strlen(tree->u.comparison.attr));
               asn1_write_OctetString(data, tree->u.comparison.value.data,
                                     tree->u.comparison.value.length);
               asn1_pop_tag(data);
                break;
 
        case LDB_OP_LESS:
                /* lessOrEqual test */
               asn1_push_tag(data, ASN1_CONTEXT(6));
               asn1_write_OctetString(data, tree->u.comparison.attr,
                                     strlen(tree->u.comparison.attr));
               asn1_write_OctetString(data, tree->u.comparison.value.data,
                                     tree->u.comparison.value.length);
               asn1_pop_tag(data);
                break;
 
        case LDB_OP_PRESENT:
                /* present test */
               asn1_push_tag(data, ASN1_CONTEXT_SIMPLE(7));
               asn1_write_LDAPString(data, tree->u.present.attr);
               asn1_pop_tag(data);
                return !data->has_error;
 
        case LDB_OP_APPROX:
                /* approx test */
               asn1_push_tag(data, ASN1_CONTEXT(8));
               asn1_write_OctetString(data, tree->u.comparison.attr,
                                     strlen(tree->u.comparison.attr));
               asn1_write_OctetString(data, tree->u.comparison.value.data,
                                     tree->u.comparison.value.length);
               asn1_pop_tag(data);
                break;
 
        case LDB_OP_EXTENDED:
		/*
		  MatchingRuleAssertion ::= SEQUENCE {
		  matchingRule    [1] MatchingRuleID OPTIONAL,
		  type            [2] AttributeDescription OPTIONAL,
		  matchValue      [3] AssertionValue,
                  dnAttributes    [4] BOOLEAN DEFAULT FALSE
                  }
                */
               asn1_push_tag(data, ASN1_CONTEXT(9));
                if (tree->u.extended.rule_id) {
                       asn1_push_tag(data, ASN1_CONTEXT_SIMPLE(1));
                       asn1_write_LDAPString(data, tree->u.extended.rule_id);
                       asn1_pop_tag(data);
                }
                if (tree->u.extended.attr) {
                       asn1_push_tag(data, ASN1_CONTEXT_SIMPLE(2));
                       asn1_write_LDAPString(data, tree->u.extended.attr);
                       asn1_pop_tag(data);
                }
               asn1_push_tag(data, ASN1_CONTEXT_SIMPLE(3));
               asn1_write_DATA_BLOB_LDAPString(data, &tree->u.extended.value);
               asn1_pop_tag(data);
               asn1_push_tag(data, ASN1_CONTEXT_SIMPLE(4));
               asn1_write_uint8(data, tree->u.extended.dnAttributes);
               asn1_pop_tag(data);
               asn1_pop_tag(data);
                break;
 
        default:
		return false;
	}
        return !data->has_error;
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

