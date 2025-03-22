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


    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        vector<function<bool (int, int)>> checks = {
            [&mat, &target](int i, int j) { return mat[i][j] == target[i][j]; },
            [&mat, &target](int i, int j) { return mat[i][j] == target[j][size(mat) - 1 - i]; },
            [&mat, &target](int i, int j) { return mat[i][j] == target[size(mat) - 1 - i][size(mat[0]) - 1 - j]; },
            [&mat, &target](int i, int j) { return mat[i][j] == target[size(mat[0]) - 1 - j][i]; },
        };
        const auto& traverse = [&mat, &target](const auto& check) {
            for (int i = 0; i < size(mat); ++i) {
                for (int j = 0; j < size(mat[0]); ++j) {
                    if (!check(i, j)) {
                        return false;
                    }
                }
            }
            return true;
        };
        for (const auto& check : checks) {
            if (traverse(check)) {
                return true;
            }
        }
        return false;
    }


