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

    int maxTrailingZeros(vector<vector<int>>& grid) {
        const auto& factor = [](int x) {
            static const array<int, 2> primes = {2, 5};
            array<int, 2> cnt = {0, 0};
            for (int i = 0; i < size(primes); ++i) {
                while (x && x % primes[i] == 0) {
                    x /= primes[i];
                    ++cnt[i];
                }
            }
            return cnt;
        };
        const auto& add = [](const auto& a, const auto& b) {
            return array<int, 2>{a[0] + b[0], a[1] + b[1]};
        };
        const auto& sub = [](const auto& a, const auto& b) {
            return array<int, 2>{a[0] - b[0], a[1] - b[1]};
        };
        const auto& count = [](const auto& a) {
            return min(a[0], a[1]);
        };

        vector<vector<array<int, 2>>> left(size(grid), vector<array<int, 2>>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            left[i][0] = factor(grid[i][0]);
            for (int j = 1; j < size(grid[0]); ++j) {
                left[i][j] = add(left[i][j - 1], factor(grid[i][j]));
            }
        }
        int result = 0;
        for (int j = 0; j < size(grid[0]); ++j) {
            array<int, 2> total = {0, 0};
            for (int i = 0; i < size(grid); ++i) {
                total = add(total, factor(grid[i][j]));
            }
            array<int, 2> up = {0, 0};
            for (int i = 0; i < size(grid); ++i) {
                const auto& right = j ? sub(left[i].back(), left[i][j - 1]) : left[i].back();
                result = max({result, count(add(left[i][j], up)), count(add(right, up))});
                up = add(up, factor(grid[i][j]));
                const auto& down = sub(total, up);
                result = max({result, count(add(left[i][j], down)), count(add(right, down))});
            }
        }
        return result;
    }

