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

def validateBinaryTreeNodes(self, n, leftChild, rightChild):
    """
    :type n: int
    :type leftChild: List[int]
    :type rightChild: List[int]
    :rtype: bool
    """
    roots = set(range(n)) - set(leftChild) - set(rightChild)
    if len(roots) != 1:
        return False
    root, = roots
    stk = [root]
    lookup = set([root])
    while stk:
        node = stk.pop()
        for c in (leftChild[node], rightChild[node]):
            if c < 0:
                continue
            if c in lookup:
                return False
            lookup.add(c)
            stk.append(c)
    return len(lookup) == n


