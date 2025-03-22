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

        int minCut(string s) {
            const int n = s.size();
            vector<vector<bool> > p(n, vector<bool>(n, false)); // p[i][j]: range [i, j] is a palindrome paritioning of s
            vector<int> f(n + 1, 0); // f[i]: minimum cuts in range [i, n - 1]

            for(int i = 0; i <= n; ++i) {
                f[i] = n - 1 - i;    // initialize f[i] to the max cuts
            }

            for (int i = n - 1; i >= 0; --i) {
                for (int j = i; j < n; ++j) {
                    // [i, j] is palindrome if only if s[i] equals to s[j] and [i + 1, j - 1] is palindrome too
                    if(s[i] == s[j] && ((j - i < 2) || p[i + 1][j - 1])) {
                        p[i][j] = true;
                        f[i] = min(f[i], f[j + 1] + 1);  // f[i] = min(f[j + 1] + 1) for each i <= j <= n - 1
                    }
                }   
            }

            return f[0];
        }

