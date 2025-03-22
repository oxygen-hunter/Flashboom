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

def maxUpgrades(self, count, upgrade, sell, money):
    """
    :type count: List[int]
    :type upgrade: List[int]
    :type sell: List[int]
    :type money: List[int]
    :rtype: List[int]
    """
    # let x be the number of sold servers
    # (c-x)*u <= m+(x*s)
    # -x <= (m-c*u)//(u+s) <= 0
    # c-x <= c+(m-c*u)//(u+s) <= c
    return [min(c+(m-c*u)//(u+s), c) for c, u, s, m in itertools.izip(count, upgrade, sell, money)]


