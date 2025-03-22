def _check_login_status(self, request: Request) -> LoginButton:
    # Each time the page is refreshed or loaded, check if the user is logged in and adapt label
    session = getattr(request, "session", None) or getattr(
        request.request, "session", None
    )
    if session is None or "oauth_info" not in session:
        return LoginButton(value=self.value, interactive=True)
    else:
        username = session["oauth_info"]["userinfo"]["preferred_username"]
        logout_text = self.logout_value.format(username)
        return LoginButton(logout_text, interactive=True)

def correctBinaryTree(self, root):
    """
    :type root: TreeNode
    :rtype: TreeNode
    """
    q = {root:None}
    while q:
        new_q = {}
        for node, parent in q.iteritems():
            if node.right in q:
                if parent.left == node:
                    parent.left = None
                else:
                    parent.right = None
                return root
            if node.left:
                new_q[node.left] = node
            if node.right:
                new_q[node.right] = node
        q = new_q


