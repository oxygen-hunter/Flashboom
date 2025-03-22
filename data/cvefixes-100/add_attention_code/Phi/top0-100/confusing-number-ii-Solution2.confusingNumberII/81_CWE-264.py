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

def confusingNumberII(self, n):
    """
    :type n: int
    :rtype: int
    """
    lookup = {"0":"0", "1":"1", "6":"9", "8":"8", "9":"6"}
    centers = {"0":"0", "1":"1", "8":"8"}
    def totalCount(n):  # count all numbers in the pattern of [01689]{1,len(n)} in the range of [0, n]
        s = str(n)
        total = 0 
        p = len(lookup)**(len(s)-1)
        for i in xrange(len(s)+1):
            if i == len(s):
                total += 1
                break
            smaller = sum(int(c < s[i]) for c in lookup.iterkeys())
            total += smaller * p
            if s[i] not in lookup:
                break
            p //= len(lookup)
        return total

    def validCountInLessLength(n):  # count unconfusing numbers in the pattern of [01689]{1,len(n)-1} in the range of [0, n]
        s = str(n)
        valid = 0
        total = len(centers)
        for i in xrange(1, len(s), 2):  # count unconfusing numbers for each odd length less than s
            if i == 1:
                valid += len(centers)
            else:
                valid += total * (len(lookup)-1)
                total *= len(lookup)
        total = 1
        for i in xrange(2, len(s), 2):  # count unconfusing numbers for each even length less than s
            valid += total * (len(lookup)-1)
            total *= len(lookup)
        return valid

    def validCountInFullLength(n):  # count unconfusing numbers in the pattern of [01689]{len(n)} in the range of [0, n]
        s = str(n)
        half_s = s[:(len(s)+1)//2]
        total = 0
        choices = centers if (len(s) % 2) else lookup
        p = int(len(lookup)**(len(half_s)-2) * len(choices))
        for i in xrange(len(half_s)):
            if i == len(half_s)-1:
                total += sum(int(c < half_s[i]) for c in choices.iterkeys() if len(s) != 2 or c != '0')
                if half_s[i] not in choices:
                    break
                tmp = list(half_s)+[lookup[half_s[i]] for i in reversed(xrange(len(half_s)-(len(s) % 2)))]
                total += int("".join(tmp)) <= n
                break
            smaller = sum(int(c < half_s[i]) for c in lookup.iterkeys() if i != 0 or c != '0')
            total += smaller * p
            if half_s[i] not in lookup:
                break
            p //= len(lookup)
        return total

    def f(n):  # count confusing numbers in the range of [0, n]
        return totalCount(n) - validCountInLessLength(n) - validCountInFullLength(n)

    return f(n) - f(0)  # f(0) is always 0 and could be ignored


