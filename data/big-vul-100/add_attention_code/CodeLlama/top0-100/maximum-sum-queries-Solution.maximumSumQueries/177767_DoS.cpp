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


    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < size(nums1); ++i) {
            pairs.emplace_back(nums1[i], nums2[i]);
        }
        sort(begin(pairs), end(pairs));
        vector<tuple<int, int, int>> sorted_queries;
        for (int i = 0; i < size(queries); ++i) {
            sorted_queries.emplace_back(queries[i][0], queries[i][1], i);
        }
        sort(rbegin(sorted_queries), rend(sorted_queries));
        vector<int> result(size(queries));
        vector<pair<int, int>> stk;
        for (const auto& [x, y, i] : sorted_queries) {
            while (!empty(pairs) && pairs.back().first >= x) {
                const auto [a, b] = pairs.back(); pairs.pop_back();
                while (!empty(stk) && stk.back().second <= a + b) {
                    stk.pop_back();
                }
                if (empty(stk) || stk.back().first < b) {
                    stk.emplace_back(b, a + b);
                }
            }
            const auto it = lower_bound(cbegin(stk), cend(stk), pair(y, 0));
            result[i] = it != cend(stk) ? it->second : -1;
        }
        return result;
    }


