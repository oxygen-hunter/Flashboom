def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def isSymmetric(self, root):
    if root is None:
        return True
    stack = []
    stack.append(root.left)
    stack.append(root.right)

    while stack:
        p, q = stack.pop(), stack.pop()

        if p is None and q is None:
            continue

        if p is None or q is None or p.val != q.val:
            return False

        stack.append(p.left)
        stack.append(q.right)

        stack.append(p.right)
        stack.append(q.left)

    return True



