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

def commonFactors(self, a, b):
    """
    :type a: int
    :type b: int
    :rtype: int
    """
    def gcd(a, b):  # Time: O(log(min(a, b)))
        while b:
            a, b = b, a%b
        return a
    
    g = gcd(a, b)
    result = 0
    x = 1
    while x*x <= g:
        if g%x == 0:
            result += 1 if g//x == x else 2
        x += 1
    return result


