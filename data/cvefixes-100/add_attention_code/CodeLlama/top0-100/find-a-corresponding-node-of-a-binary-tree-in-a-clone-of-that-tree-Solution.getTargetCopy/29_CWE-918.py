def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def getTargetCopy(self, original, cloned, target):
    """
    :type original: TreeNode
    :type cloned: TreeNode
    :type target: TreeNode
    :rtype: TreeNode
    """
    def preorder_gen(node):
        stk = [node]
        while stk:
            node = stk.pop()
            if not node:
                continue
            yield node
            stk.append(node.right)
            stk.append(node.left)
        
    for node1, node2 in itertools.izip(preorder_gen(original),
                                       preorder_gen(cloned)):
        if node1 == target:
            return node2


