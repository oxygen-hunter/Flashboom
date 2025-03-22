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

    vector<int> findXSum(vector<int>& nums, int k, int x) {
        using ordered_set = tree<pair<int, int>, null_type, greater<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>;
        ordered_set os;
        unordered_map<int, int> cnt;
        const auto& update = [&](int v, int d, int curr) {
            if (d == 1) {
                os.insert({cnt[v], v});
            }

            if (os.order_of_key(pair(cnt[v], v)) < x) {
                curr += d * cnt[v] * v;
                if (x < size(os)) {
                    const auto [nc, nv] = *(os.find_by_order(x));
                    curr -= d * nc * nv;
                }
            }
            if (d != 1) {
                os.erase(pair(cnt[v], v));
            }
            return curr;
        };

        vector<int> result;
        for (int i = 0, curr = 0; i < size(nums); ++i) {
            if (cnt.count(nums[i])) {
                curr = update(nums[i], -1, curr);
            }
            ++cnt[nums[i]];
            curr = update(nums[i], +1, curr);
            if (i < k - 1) {
                continue;
            }
            result.emplace_back(curr);
            curr = update(nums[i - (k - 1)], -1, curr);
            --cnt[nums[i - (k - 1)]];
            if (cnt[nums[i - (k - 1)]]) {
                curr = update(nums[i - (k - 1)], +1, curr);
            } else {
                cnt.erase(nums[i - (k - 1)]);
            }
        }
        return result;
    }

