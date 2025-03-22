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

def canMerge(self, trees):
    """
    :type trees: List[TreeNode]
    :rtype: TreeNode
    """
    def find_leaves_and_roots(trees, leaf_vals_set, val_to_root):
        for root in trees:
            val_to_root[root.val] = root
            q = [root]
            while q:
                new_q = []
                for node in q:
                    if node.left is None and node.right is None:
                        if node is not root:
                            leaf_vals_set.add(node.val)
                        continue
                    if node.left:
                        new_q.append(node.left)
                    if node.right:
                        new_q.append(node.right)
                q = new_q

    def find_root(trees, left_vals_set, val_to_root):
        root = None
        for node in trees:
            if node.val in leaf_vals_set:
                continue
            if root:  # multiple roots
                return None
            root = node
        return root

    def merge_bsts(root, left_vals_set, val_to_root):
        if not root:
            return None
        del val_to_root[root.val]
        q = [(root, float("-inf"), float("inf"))]
        while q:
            new_q = []
            for node, left, right in q:
                if not (left < node.val < right):
                    return None
                if node.left:
                    if node.left.val in leaf_vals_set and node.left.val in val_to_root:
                        node.left = val_to_root[node.left.val]
                        del val_to_root[node.left.val]
                    new_q.append((node.left, left, node.val))
                if node.right:
                    if node.right.val in leaf_vals_set and node.right.val in val_to_root:
                        node.right = val_to_root[node.right.val]
                        del val_to_root[node.right.val]
                    new_q.append((node.right, node.val, right))
            q = new_q
        return root if not val_to_root else None

    leaf_vals_set, val_to_root = set(), {}
    find_leaves_and_roots(trees, leaf_vals_set, val_to_root)    
    root = find_root(trees, leaf_vals_set, val_to_root)
    return merge_bsts(root, leaf_vals_set, val_to_root)


