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

def digitsCount(self, d, low, high):
    """
    :type d: int
    :type low: int
    :type high: int
    :rtype: int
    """
    def digitsCount(n, k):
        pivot, result = 1, 0
        while n >= pivot:
            result += (n//(10*pivot))*pivot + \
                       min(pivot, max(n%(10*pivot) - k*pivot + 1, 0))
            if k == 0:
                result -= pivot
            pivot *= 10
        return result+1
    
    return digitsCount(high, d) - digitsCount(low-1, d)


