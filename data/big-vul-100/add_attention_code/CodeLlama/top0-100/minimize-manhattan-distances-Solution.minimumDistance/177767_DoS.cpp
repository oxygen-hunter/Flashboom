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


    int minimumDistance(vector<vector<int>>& points) {
        const auto& max_distance = [&](int exclude) {
            static const int POS_INF = numeric_limits<int>::max();
            static const int NEG_INF = numeric_limits<int>::min();
    
            pair<int, int> max_sum = {NEG_INF, -1};
            pair<int, int> min_sum = {POS_INF, -1};
            pair<int, int> max_diff = {NEG_INF, -1};
            pair<int, int> min_diff = {POS_INF, -1};
            for (int i = 0; i < size(points); ++i) {
                if (i == exclude) {
                    continue;
                }
                const int x = points[i][0], y = points[i][1];
                max_sum = max(max_sum, {x + y, i});
                min_sum = min(min_sum, {x + y, i});
                max_diff = max(max_diff, {x - y, i});
                min_diff = min(min_diff, {x - y, i});
            }
            return max(tuple{max_sum.first - min_sum.first, max_sum.second, min_sum.second},
                       tuple{max_diff.first - min_diff.first, max_diff.second, min_diff.second});
        };
    
        const auto& [_, i, j] = max_distance(-1);
        return min(get<0>(max_distance(i)), get<0>(max_distance(j)));
    }


