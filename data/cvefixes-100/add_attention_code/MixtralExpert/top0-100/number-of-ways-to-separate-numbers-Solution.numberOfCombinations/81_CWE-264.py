def authenticate(self, context, auth=None):
    """Authenticate credentials and return a token.

    Accept auth as a dict that looks like::

        {
            "auth":{
                "passwordCredentials":{
                    "username":"test_user",
                    "password":"mypass"
                },
                "tenantName":"customer-x"
            }
        }

    In this case, tenant is optional, if not provided the token will be
    considered "unscoped" and can later be used to get a scoped token.

    Alternatively, this call accepts auth with only a token and tenant
    that will return a token that is scoped to that tenant.
    """

    token_id = uuid.uuid4().hex
    if 'passwordCredentials' in auth:
        username = auth['passwordCredentials'].get('username', '')
        password = auth['passwordCredentials'].get('password', '')
        tenant_name = auth.get('tenantName', None)

        user_id = auth['passwordCredentials'].get('userId', None)
        if username:
            user_ref = self.identity_api.get_user_by_name(
                    context=context, user_name=username)
            if user_ref:
                user_id = user_ref['id']

        # more compat
        tenant_id = auth.get('tenantId', None)
        if tenant_name:
            tenant_ref = self.identity_api.get_tenant_by_name(
                    context=context, tenant_name=tenant_name)
            if tenant_ref:
                tenant_id = tenant_ref['id']

        try:
            auth_info = self.identity_api.authenticate(context=context,
                                                        user_id=user_id,
                                                        password=password,
                                                        tenant_id=tenant_id)
            (user_ref, tenant_ref, metadata_ref) = auth_info

            # If the user is disabled don't allow them to authenticate
            if not user_ref.get('enabled', True):
                LOG.warning('User %s is disabled' % user_id)
                raise exception.Unauthorized()
        except AssertionError as e:
            raise exception.Unauthorized(e.message)

        token_ref = self.token_api.create_token(
                context, token_id, dict(id=token_id,
                                        user=user_ref,
                                        tenant=tenant_ref,
                                        metadata=metadata_ref))
        if tenant_ref:
            catalog_ref = self.catalog_api.get_catalog(
                    context=context,
                    user_id=user_ref['id'],
                    tenant_id=tenant_ref['id'],
                    metadata=metadata_ref)
        else:
            catalog_ref = {}

    elif 'token' in auth:
        token = auth['token'].get('id', None)

        tenant_name = auth.get('tenantName')

        # more compat
        if tenant_name:
            tenant_ref = self.identity_api.get_tenant_by_name(
                    context=context, tenant_name=tenant_name)
            tenant_id = tenant_ref['id']
        else:
            tenant_id = auth.get('tenantId', None)

        try:
            old_token_ref = self.token_api.get_token(context=context,
                                                        token_id=token)
        except exception.NotFound:
            raise exception.Unauthorized()

        user_ref = old_token_ref['user']

        # If the user is disabled don't allow them to authenticate
        current_user_ref = self.identity_api.get_user(
                                                context=context,
                                                user_id=user_ref['id'])
        if not current_user_ref.get('enabled', True):
            LOG.warning('User %s is disabled' % user_ref['id'])
            raise exception.Unauthorized()

        tenants = self.identity_api.get_tenants_for_user(context,
                                                            user_ref['id'])
        if tenant_id:
            assert tenant_id in tenants

        tenant_ref = self.identity_api.get_tenant(context=context,
                                                    tenant_id=tenant_id)
        if tenant_ref:
            metadata_ref = self.identity_api.get_metadata(
                    context=context,
                    user_id=user_ref['id'],
                    tenant_id=tenant_ref['id'])
            catalog_ref = self.catalog_api.get_catalog(
                    context=context,
                    user_id=user_ref['id'],
                    tenant_id=tenant_ref['id'],
                    metadata=metadata_ref)
        else:
            metadata_ref = {}
            catalog_ref = {}

        token_ref = self.token_api.create_token(
                context, token_id, dict(id=token_id,
                                        user=user_ref,
                                        tenant=tenant_ref,
                                        metadata=metadata_ref))

    # TODO(termie): optimize this call at some point and put it into the
    #               the return for metadata
    # fill out the roles in the metadata
    roles_ref = []
    for role_id in metadata_ref.get('roles', []):
        roles_ref.append(self.identity_api.get_role(context, role_id))
    logging.debug('TOKEN_REF %s', token_ref)
    return self._format_authenticate(token_ref, roles_ref, catalog_ref)

def numberOfCombinations(self, num):
    """
    :type num: str
    :rtype: int
    """
    MOD = 10**9+7
    def find_longest_common_prefix(num):
        lcp = [[0]*(len(num)+1) for _ in xrange(len(num)+1)]  # lcp[i][j]: longest length of the common prefix which starts at num[i], num[j]
        for i in reversed(xrange(len(lcp)-1)):
            for j in reversed(xrange(len(lcp[0])-1)):
                if num[i] == num[j]:
                    lcp[i][j] = lcp[i+1][j+1]+1
        return lcp

    def is_less_or_equal_to_with_same_length(num, lcp, i, j, l):
        return lcp[i][j] >= l or num[i+lcp[i][j]] < num[j+lcp[i][j]]

    lcp = find_longest_common_prefix(num)
    dp = [[0]*len(num) for _ in xrange(len(num))]  # dp[i][l]: the count of numbers ending at num[i], where the length of the last number is l+1
    dp[0][0] = int(num[0] != '0')
    for i in xrange(1, len(num)):
        dp[i][i] = dp[i-1][i-1]
        if num[i] == '0':
            continue
        accu = 0
        for l in xrange(len(num)-i+1):
            ni = i+l-1
            dp[ni][l-1] = accu  # accumulated count where the length of the second to last number ending at num[i-1] is shorter than the length of the last number ending at num[i+l-1]
            if i-l < 0:
                continue
            if num[i-l] != '0' and is_less_or_equal_to_with_same_length(num, lcp, i-l, i, l):
                dp[ni][l-1] = (dp[ni][l-1] + dp[i-1][l-1]) % MOD
            accu = (accu + dp[i-1][l-1]) % MOD
    return reduce(lambda total, x: (total+x)%MOD, dp[-1], 0)


