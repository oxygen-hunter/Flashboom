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


    int waysToReachStair(int k) {
        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };

        const auto& ceil_log2_x = [&](int x) {
            return bit_length(x - 1);
        };
    
        int l = ceil_log2_x(k);
        for (; (1ll << l) - k <= l + 1; ++l);
        vector<__int128> fact(l + 1, 1);
        for (int i = 0; i + 1 < size(fact); ++i) {
            fact[i + 1] = fact[i] * (i + 1);
        }
        const auto& nCr = [&](int n, int r) {
            if (!(0 <= r && r <= n)) {
                return static_cast<__int128>(0);
            }
            return fact[n] / fact[r] / fact[n - r];
        };

        int result = 0;
        for (int i = 0; i < l; ++i) {
            result += nCr(i + 1, (1 << i) - k);
        }
        return result;
    }


