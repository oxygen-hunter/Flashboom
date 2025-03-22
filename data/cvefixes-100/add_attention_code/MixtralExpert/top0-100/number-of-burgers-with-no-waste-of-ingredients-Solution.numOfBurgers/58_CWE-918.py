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

def numOfBurgers(self, tomatoSlices, cheeseSlices):
    """
    :type tomatoSlices: int
    :type cheeseSlices: int
    :rtype: List[int]
    """
    # let the number of jumbo burger be x, the number of small burger be y:
    #   4x + 2y = t
    #   x + y = c
    #   =>
    #   x = t/2-c
    #   y = 2c-t/2
    # since x, y are natural numbers
    #   => t/2 is integer, t/2-c >= 0, 2c-t/2 >= 0
    #   => t%2 == 0, 2c <= t <= 4c
    return [tomatoSlices//2-cheeseSlices, 2*cheeseSlices - tomatoSlices//2] \
           if tomatoSlices%2 == 0 and 2*cheeseSlices <= tomatoSlices <= 4*cheeseSlices \
           else []


