def set_bookmark(book_id, book_format):
    bookmark_key = request.form["bookmark"]
    ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                              ub.Bookmark.book_id == book_id,
                                              ub.Bookmark.format == book_format)).delete()
    if not bookmark_key:
        ub.session_commit()
        return "", 204

    lbookmark = ub.Bookmark(user_id=current_user.id,
                            book_id=book_id,
                            format=book_format,
                            bookmark_key=bookmark_key)
    ub.session.merge(lbookmark)
    ub.session_commit("Bookmark for user {} in book {} created".format(current_user.id, book_id))
    return "", 201

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


