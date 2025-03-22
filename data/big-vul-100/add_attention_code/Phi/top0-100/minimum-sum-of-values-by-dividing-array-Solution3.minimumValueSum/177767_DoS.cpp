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

    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        static const int INF = numeric_limits<int>::max();

        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };

        const int FULL_MASK = (1 << bit_length(ranges::max(nums))) - 1;
        vector<vector<unordered_map<int, int>>> lookup(size(nums), vector<unordered_map<int, int>>(size(andValues)));
        const function<int (int, int, int)> memoization = [&](int i, int j, int mask) {
            if (i == size(nums) && j == size(andValues)) {
                return 0;
            }
            if (i == size(nums) || j == size(andValues) || mask < andValues[j]) {
                return INF;
            }
            if (!lookup[i][j].count(mask)) {
                int curr = memoization(i + 1, j, mask & nums[i]);
                if ((mask & nums[i]) == andValues[j]) {
                    const int total = memoization(i + 1, j + 1, FULL_MASK);
                    if (total != INF) {
                        curr = min(curr, nums[i] + total);
                    }
                }
                lookup[i][j][mask] = curr;
            }
            return lookup[i][j][mask];
        };

        const int result = memoization(0, 0, FULL_MASK);
        return result != INF ? result : -1;
    }

