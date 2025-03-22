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

    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        static const double EPS = 1e-15;
        static const int MOD = 1e9 + 7;
        const auto& powmod = [&](int a, int b) {
            a %= MOD;
            int64_t result = 1;
            while (b) {
                if (b & 1) {
                    result = result * a % MOD;
                }
                a = int64_t(a) * a % MOD;
                b >>= 1;
            }
            return result;
        };

        const auto& binary_search_right = [](auto left, auto right, const auto& check) {
            while (left <= right) {
                const auto mid = left + (right - left) / 2;
                if (!check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return right;
        };

        const auto& count = [](const auto& x, int target) {
            return static_cast<int>(target - x + EPS);
        };

        if (multiplier == 1) {
            return nums;
        }
        using P = pair<double, int>;
        vector<P> vals;
        for (int i = 0; i < size(nums); ++i) {
            vals.emplace_back(log(nums[i]) / log(multiplier), i);
        }
        sort(begin(vals), end(vals));
        const auto& check = [&](const auto& target) {
            int result = 0;
            for (const auto& [x, i] : vals) {
                const int c = count(x, target);
                if (c <= 0) {
                    break;
                }
                result += c;
            }
            return result <= k;
        };

        const int target = binary_search_right(1, static_cast<int>(vals.back().first) + 1, check);
        vector<int64_t> nums2(cbegin(nums), cend(nums));
        for (int idx = 0; idx < size(vals); ++idx) {
            const auto& [x, i] = vals[idx];
            const int c = count(x, target);
            if (c <= 0) {
                break;
            }
            k -= c;
            nums2[i] *= pow(multiplier, c);
        }
        using P2 = pair<int64_t, int>;
        vector<P2> vals2;
        for (int i = 0; i < size(nums2); ++i) {
            vals2.emplace_back(nums2[i], i);
        }
        sort(begin(vals2), end(vals2));
        const int q = k / size(nums), r = k % size(nums);
        const int m = powmod(multiplier, q);
        vector<int> result(size(nums));
        for (int idx = 0; idx < size(vals2); ++idx) {
            const auto& [x, i] = vals2[idx];
            result[i] = ((x % MOD * m) % MOD * (idx < r ? multiplier : 1)) % MOD;
        }
        return result;
    }

