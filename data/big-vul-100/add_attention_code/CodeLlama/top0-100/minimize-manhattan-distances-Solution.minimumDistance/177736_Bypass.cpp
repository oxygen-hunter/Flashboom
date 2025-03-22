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


    int minimumDistance(vector<vector<int>>& points) {
        const auto& max_distance = [&](int exclude) {
            static const int POS_INF = numeric_limits<int>::max();
            static const int NEG_INF = numeric_limits<int>::min();
    
            pair<int, int> max_sum = {NEG_INF, -1};
            pair<int, int> min_sum = {POS_INF, -1};
            pair<int, int> max_diff = {NEG_INF, -1};
            pair<int, int> min_diff = {POS_INF, -1};
            for (int i = 0; i < size(points); ++i) {
                if (i == exclude) {
                    continue;
                }
                const int x = points[i][0], y = points[i][1];
                max_sum = max(max_sum, {x + y, i});
                min_sum = min(min_sum, {x + y, i});
                max_diff = max(max_diff, {x - y, i});
                min_diff = min(min_diff, {x - y, i});
            }
            return max(tuple{max_sum.first - min_sum.first, max_sum.second, min_sum.second},
                       tuple{max_diff.first - min_diff.first, max_diff.second, min_diff.second});
        };
    
        const auto& [_, i, j] = max_distance(-1);
        return min(get<0>(max_distance(i)), get<0>(max_distance(j)));
    }


