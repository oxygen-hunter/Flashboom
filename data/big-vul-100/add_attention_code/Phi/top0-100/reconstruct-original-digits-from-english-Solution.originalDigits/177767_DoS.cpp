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

    string originalDigits(string s) {
        const vector<string> numbers{"zero", "one", "two", "three",
                                     "four", "five", "six", "seven",
                                     "eight", "nine"};
        vector<vector<int>> cnts(numbers.size(), vector<int>(26));
        for (int i = 0; i < numbers.size(); ++i) {
            for (const auto& c : numbers[i]) {
                ++cnts[i][c - 'a'];
            }
        }
        
        // The order for greedy method.
        vector<int> order{0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
        
        // The unique char in the order.
        vector<char> unique_chars{'z', 'o', 'w', 't', 'u', 'f', 'x', 's', 'g', 'n'};
        vector<int> cnt(26);
        for (const auto& c : s) {
            ++cnt[c - 'a'];
        }

        string result;
        for (const auto& i : order) {
            while (cnt[unique_chars[i] - 'a'] > 0) {
                for (int j = 0; j < cnt.size(); ++j) {
                    cnt[j] -= cnts[i][j];
                }
                result.push_back(i + '0');
            }
        }
        sort(result.begin(), result.end());
        return result;
    }

