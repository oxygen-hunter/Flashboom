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


    vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
        for (int i = 0, mx_i = 0, mn_i = 0; i + indexDifference < size(nums); ++i) {
            if (nums[i] > nums[mx_i]) {
                mx_i = i;
            } else if (nums[i] < nums[mn_i]) {
                mn_i = i;
            }
            // we don't need to add abs for the difference since
            // - if nums[mx_i]-nums[i+indexDifference] < 0, then checking nums[i+indexDifference]-nums[mn_i] >= -(nums[mx_i]-nums[i+indexDifference]) > 0 can cover the case
            // - if nums[i+indexDifference]-nums[mn_i] < 0, then checking nums[mx_i]-nums[i+indexDifference] >= -(nums[i+indexDifference]-nums[mn_i]) > 0 can cover the case
            if (nums[mx_i] - nums[i + indexDifference] >= valueDifference) {
                return {mx_i, i + indexDifference};
            }
            if (nums[i + indexDifference] - nums[mn_i] >= valueDifference) {
                return {mn_i, i + indexDifference};
            }
        }
        return {-1, -1};
    }


