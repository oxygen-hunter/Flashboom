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

    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        vector<pair<int, int>> q = {{start[0], start[1]}};
        vector<vector<int>> lookup(size(grid), vector<int>(size(grid[0]), -1));
        int d = lookup[start[0]][start[1]] = 0;
        auto compare = [&](const auto& x, const auto& y) {
            return make_tuple(lookup[x[0]][x[1]], grid[x[0]][x[1]], x[0], x[1]) <
                   make_tuple(lookup[y[0]][y[1]], grid[y[0]][y[1]], y[0], y[1]);
        };
        vector<vector<int>> result;
        while (!empty(q)) {
            if (size(result) >= k) {
                if (size(result) > k) {
                    nth_element(begin(result), begin(result) + k, end(result), compare);
                    result.resize(k);
                }
                break;
            }
            vector<pair<int, int>> new_q;
            for (const auto& [r, c] : q) {
                if (pricing[0] <= grid[r][c] && grid[r][c] <= pricing[1]) {
                    result.push_back({r, c});
                }
                for (const auto& [dr, dc] : directions) {
                    const int nr = r + dr, nc = c + dc;
                    if (!((0 <= nr && nr < size(grid)) && (0 <= nc && nc < size(grid[0])) &&
                           grid[nr][nc] && lookup[nr][nc] == -1)) {
                        continue;
                    }
                    lookup[nr][nc] = d + 1;
                    new_q.emplace_back(nr, nc);
                }
            }
            q = move(new_q);
            ++d;
        }
        sort(begin(result), end(result), compare);
        return result;
    }

