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

    int backtracking(const vector<string>& pieces, const vector<vector<int>>& positions, int i, vector<vector<int>> *lookup) {
        static const unordered_map<string, vector<pair<int, int>>> directions = {
            {"rook", {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}},
            {"bishop", {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}},
            {"queen", {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}}
        };
        static const int all_mask = (1 << 7) - 1;  // at most 7 seconds in 8x8 board

        if (i == size(pieces)) {
            return 1;
        }
        int result = 0;
        int r = positions[i][0] - 1, c = positions[i][1] - 1;
        int mask = all_mask;
        if (!((*lookup)[r][c] & mask)) {
            (*lookup)[r][c] += mask;  // stopped at (r, c)
            result += backtracking(pieces, positions, i + 1, lookup);
            (*lookup)[r][c] -= mask;
        }
        for (const auto& [dr, dc] : directions.at(pieces[i])) {
            int bit = 1, nr = r + dr, nc = c + dc;
            int mask = all_mask;  // (mask&bit == 1): (log2(bit)+1)th second is occupied
            for (; 0 <= nr && nr < 8 && 0 <= nc && nc < 8 && !((*lookup)[nr][nc] & bit); bit <<= 1, nr += dr, nc += dc) {
                (*lookup)[nr][nc] += bit;
                mask -= bit;
                if (!((*lookup)[nr][nc] & mask)) {  // stopped at (nr, nc)
                    (*lookup)[nr][nc] += mask;
                    result += backtracking(pieces, positions, i + 1, lookup);
                    (*lookup)[nr][nc] -= mask;
                }
            }
            while (bit >> 1) {
                bit >>= 1, nr -= dr, nc -= dc;
                (*lookup)[nr][nc] -= bit;
            }
        }
        return result;
    }

