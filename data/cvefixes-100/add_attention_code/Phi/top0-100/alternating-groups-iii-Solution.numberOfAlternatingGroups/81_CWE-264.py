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

def numberOfAlternatingGroups(self, colors, queries):
    """
    :type colors: List[int]
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    class BIT(object):  # 0-indexed.
        def __init__(self, n):
            self.__bit = [0]*(n+1)

        def add(self, i, val):
            i += 1
            while i < len(self.__bit):
                self.__bit[i] += val
                i += (i & -i)

        def query(self, i):
            i += 1
            ret = 0
            while i > 0:
                ret += self.__bit[i]
                i -= (i & -i)
            return ret

    def update(i, d):
        if d == +1:
            sl.add(i)
            if len(sl) == 1:
                bit1.add(n, +1)
                bit2.add(n, +n)
        curr = sl.index(i)
        prv, nxt = (curr-1)%len(sl), (curr+1)%len(sl)
        if len(sl) != 1:
            l = (sl[nxt]-sl[prv]-1)%n+1
            bit1.add(l, d*(-1))
            bit2.add(l, d*(-l))
            l = (sl[curr]-sl[prv])%n
            bit1.add(l, d*(+1))
            bit2.add(l, d*(+l))
            l = (sl[nxt]-sl[curr])%n
            bit1.add(l, d*(+1))
            bit2.add(l, d*(+l))
        if d == -1:
            if len(sl) == 1:
                bit1.add(n, -1)
                bit2.add(n, -n)
            sl.pop(curr)

    n = len(colors)
    sl = SortedList()
    bit1, bit2 = BIT(n+1), BIT(n+1)
    for i in xrange(n):
        if colors[i] == colors[(i+1)%n]:
            update(i, +1)
    result = []
    for q in queries:
        if q[0] == 1:
            l = q[1]
            result.append((bit2.query(n)-bit2.query(l-1))-
                          (l-1)*(bit1.query(n)-bit1.query(l-1)) if sl else n)
            continue
        _, i, c = q
        if colors[i] == c:
            continue      
        colors[i] = c          
        update((i-1)%n, +1 if colors[i] == colors[(i-1)%n] else -1) 
        update(i, +1 if colors[i] == colors[(i+1)%n] else -1)
    return result


