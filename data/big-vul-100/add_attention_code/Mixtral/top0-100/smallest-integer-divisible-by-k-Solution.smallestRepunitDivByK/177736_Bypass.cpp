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

    int smallestRepunitDivByK(int K) {
        // by observation, K % 2 = 0 or K % 5 = 0, it is impossible
        if (K % 2 == 0 || K % 5 == 0) {
            return -1;
        }
        // let f(N) is a N-length integer only containing digit 1
        // given K % 2 != 0 and K % 5 != 0
        // if there is no N in range (1..K) s.t. f(N) % K = 0
        // => there must be K remainders of f(N) % K in range (1..K-1) excluding 0
        // => due to pigeonhole principle, there must be at least 2 same remainders
        // => there must be some x, y in range (1..K) and x > y s.t. f(x) % K = f(y) % K
        // => (f(x) - f(y)) % K = 0
        // => (f(x-y) * 10^y) % K = 0
        // => due to (x-y) in range (1..K)
        // => f(x-y) % K != 0
        // => 10^y % K = 0
        // => K % 2 = 0 or K % 5 = 0
        // => -><-
        // it proves that there must be some N in range (1..K) s.t. f(N) % K = 0
        int result = 0;
        for (int N = 1; N <= K; ++N) {
            result = (result * 10 + 1) % K;
            if (!result) {
                return N;
            }
        }
        assert(false);
        return -1;  // never reach
    }

