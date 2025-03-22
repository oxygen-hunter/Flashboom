static bool decode_openldap_dereference(void *mem_ctx, DATA_BLOB in, void *_out)
{
	void **out = (void **)_out;
	struct asn1_data *data = asn1_init(mem_ctx);
	struct dsdb_openldap_dereference_result_control *control;
	struct dsdb_openldap_dereference_result **r = NULL;
	int i = 0;
	if (!data) return false;

	control = talloc(mem_ctx, struct dsdb_openldap_dereference_result_control);
	if (!control) return false;

	if (!asn1_load(data, in)) {
		return false;
	}

	control = talloc(mem_ctx, struct dsdb_openldap_dereference_result_control);
	if (!control) {
		return false;
	}

	if (!asn1_start_tag(data, ASN1_SEQUENCE(0))) {
		return false;
	}

	while (asn1_tag_remaining(data) > 0) {					
		r = talloc_realloc(control, r, struct dsdb_openldap_dereference_result *, i + 2);
		if (!r) {
			return false;
		}
		r[i] = talloc_zero(r, struct dsdb_openldap_dereference_result);
		if (!r[i]) {
			return false;
		}

		if (!asn1_start_tag(data, ASN1_SEQUENCE(0))) {
			return false;
		}
		
		asn1_read_OctetString_talloc(r[i], data, &r[i]->source_attribute);
		asn1_read_OctetString_talloc(r[i], data, &r[i]->dereferenced_dn);
		if (asn1_peek_tag(data, ASN1_CONTEXT(0))) {
                        if (!asn1_start_tag(data, ASN1_CONTEXT(0))) {
                                return false;
                        }
                       ldap_decode_attribs_bare(r, data, &r[i]->attributes,
                                                &r[i]->num_attributes);
                        if (!asn1_end_tag(data)) {
                                return false;
                        }
		}
		if (!asn1_end_tag(data)) {
			return false;
		}
		i++;
		r[i] = NULL;
	}

	if (!asn1_end_tag(data)) {
		return false;
	}

	control->attributes = r;
	*out = control;

	return true;
}

    int minimumLines(vector<vector<int>>& points) {
        auto ceil_divide = [](int a, int b) {
            return (a + b - 1) / b;
        };
        unordered_map<tuple<int, int, int>, unordered_set<pair<int, int>, PairHash<int>>, TupleHash<int, int, int>> lookup;
        for (int i = 0; i < size(points); ++i) {
            const int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < size(points); ++j) {
                const int x2 = points[j][0], y2 = points[j][1];
                // (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
                // => (y2-y1)x - (x2-x1)y = x1(y2-y1) - y1(x2-x1)
                int a = y2 - y1;
                int b = -(x2 - x1);
                int c = x1 * (y2 - y1) - y1 * (x2 - x1);
                const int g = gcd(gcd(a, b), c);
                a /= g, b /= g, c /= g;
                lookup[{a, b, c}].emplace(x1, y1);
                lookup[{a, b, c}].emplace(x2, y2);
            }
        }
        vector<tuple<int, int, int>> lines;
        for (const auto& [l, p] : lookup) {
            if (size(p) > 2) {  // filter to improve complexity
                lines.emplace_back(l);
            }
        }
        assert(size(lines) <= size(points) / 2);  // 1 extra colinear point per 2 points
        int result = numeric_limits<int>::max();
        const int mask_upper_bound = 1 << size(lines);
        for (int mask = 0; mask < mask_upper_bound; ++mask) {
            unordered_set<pair<int, int>, PairHash<int>> covered;
            for (int i = 0, bit = 1; bit <= mask; bit <<= 1, ++i) {
                if (mask & bit) {
                    for (const auto& x : lookup[lines[i]]) {
                        covered.emplace(x);
                    }
                }
            }
            result = min(result, __builtin_popcount(mask) + ceil_divide(size(points) - size(covered), 2));
        }
        return result;
    }

