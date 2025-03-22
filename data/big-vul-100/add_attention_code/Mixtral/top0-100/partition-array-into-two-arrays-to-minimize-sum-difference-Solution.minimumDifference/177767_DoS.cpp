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

    int minimumDifference(vector<int>& nums) {
        vector<int> left, right; 
        for (int i = 0; i < size(nums); ++i) {
            if (i < size(nums) / 2) {
                left.emplace_back(nums[i]); 
            } else {
                right.emplace_back(nums[i]); 
            }
        }
        const auto& total1 = accumulate(cbegin(left), cend(left), 0);
        const auto& total2 = accumulate(cbegin(right), cend(right), 0);
        const int bound = (1 << size(left));
        unordered_map<int, vector<int>> sums;
        for (int mask = 0; mask < bound; ++mask) {
            int total = 0, bit = 1;
            for (const auto& x : left) {
                if (mask & bit) {
                    total += x; 
                }
                bit <<= 1;
            }
            sums[__builtin_popcount(mask)].emplace_back(2 * total - total1); 
        }
        for (auto& [_, v] : sums) {
            sort(begin(v), end(v));
        }
        int result = numeric_limits<int>::max();
        for (int mask = 0; mask < bound; ++mask) {
            int total = 0, bit = 1;
            for (const auto& x : right) {
                if (mask & bit) {
                    total += x; 
                }
                bit <<= 1;
            }
            const int k = size(right) - __builtin_popcount(mask);
            const int diff = 2 * total - total2; 
            const auto cit = lower_bound(cbegin(sums[k]), cend(sums[k]), -diff); 
            if (cit != cend(sums[k])) {
                result = min(result, abs(*cit + diff)); 
            }
            if (cit != cbegin(sums[k])) {
                result = min(result, abs(*prev(cit) + diff));    
            }
        }
        return result; 
    }

