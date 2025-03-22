static int samldb_check_user_account_control_acl(struct samldb_ctx *ac,
						 struct dom_sid *sid,
						 uint32_t user_account_control,
						 uint32_t user_account_control_old)
{
	int i, ret = 0;
	bool need_acl_check = false;
	struct ldb_result *res;
	const char * const sd_attrs[] = {"ntSecurityDescriptor", NULL};
        struct security_token *user_token;
        struct security_descriptor *domain_sd;
        struct ldb_dn *domain_dn = ldb_get_default_basedn(ldb_module_get_ctx(ac->module));
        const struct uac_to_guid {
                uint32_t uac;
                const char *oid;
                const char *guid;
                enum sec_privilege privilege;
                bool delete_is_privileged;
                const char *error_string;
        } map[] = {
                {
		},
		{
			.uac = UF_DONT_EXPIRE_PASSWD,
			.guid = GUID_DRS_UNEXPIRE_PASSWORD,
			.error_string = "Adding the UF_DONT_EXPIRE_PASSWD bit in userAccountControl requires the Unexpire-Password right that was not given on the Domain object"
		},
		{
			.uac = UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED,
			.guid = GUID_DRS_ENABLE_PER_USER_REVERSIBLY_ENCRYPTED_PASSWORD,
			.error_string = "Adding the UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED bit in userAccountControl requires the Enable-Per-User-Reversibly-Encrypted-Password right that was not given on the Domain object"
		},
		{
			.uac = UF_SERVER_TRUST_ACCOUNT,
			.guid = GUID_DRS_DS_INSTALL_REPLICA,
			.error_string = "Adding the UF_SERVER_TRUST_ACCOUNT bit in userAccountControl requires the DS-Install-Replica right that was not given on the Domain object"
		},
		{
			.uac = UF_PARTIAL_SECRETS_ACCOUNT,
			.guid = GUID_DRS_DS_INSTALL_REPLICA,
			.error_string = "Adding the UF_PARTIAL_SECRETS_ACCOUNT bit in userAccountControl requires the DS-Install-Replica right that was not given on the Domain object"
		},
                        .guid = GUID_DRS_DS_INSTALL_REPLICA,
                        .error_string = "Adding the UF_PARTIAL_SECRETS_ACCOUNT bit in userAccountControl requires the DS-Install-Replica right that was not given on the Domain object"
                },
                {
                        .uac = UF_INTERDOMAIN_TRUST_ACCOUNT,
                        .oid = DSDB_CONTROL_PERMIT_INTERDOMAIN_TRUST_UAC_OID,
			.error_string = "Updating the UF_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION bit in userAccountControl is not permitted without the SeEnableDelegationPrivilege"
		}

	};

    int maxPartitionsAfterOperations(string s, int k) {
        vector<int> left(size(s) + 1);
        vector<int> left_mask(size(s) + 1);
        for (int i = 0, cnt = 0, mask = 0; i < size(s); ++i) {
            mask |= 1 << (s[i] - 'a');
            if (__builtin_popcount(mask) > k) {
                ++cnt;
                mask = 1 << (s[i] - 'a');
            }
            left[i + 1] = cnt;
            left_mask[i + 1] = mask;
        }
        vector<int> right(size(s) + 1);
        vector<int> right_mask(size(s) + 1);
        for (int i = size(s) - 1, cnt = 0, mask = 0; i >= 0; --i) {
            mask |= 1 << (s[i] - 'a');
            if (__builtin_popcount(mask) > k) {
                ++cnt;
                mask = 1 << (s[i] - 'a');
            }
            right[i] = cnt;
            right_mask[i] = mask;
        }

        int result = 0;
        for (int i = 0; i < size(s); ++i) {
            int curr = left[i] + right[i + 1];
            const int mask = left_mask[i] | right_mask[i + 1];
            if (__builtin_popcount(left_mask[i]) == k && __builtin_popcount(right_mask[i + 1]) == k && __builtin_popcount(mask) != 26) {
                curr += 3;
            } else if (__builtin_popcount(mask) + (__builtin_popcount(mask) != 26 ? 1 : 0) > k) {  // test case: s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", k = 26
                curr += 2;
            } else {
                curr += 1;
            }
            result = max(result, curr);
        }
        return result;
    }

