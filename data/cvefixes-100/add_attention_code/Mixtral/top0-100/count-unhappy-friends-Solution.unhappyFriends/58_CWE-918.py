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

def unhappyFriends(self, n, preferences, pairs):
    """
    :type n: int
    :type preferences: List[List[int]]
    :type pairs: List[List[int]]
    :rtype: int
    """
    friends = [[0]*n for _ in xrange(n)]
    for i in xrange(len(preferences)):
        for j in xrange(len(preferences[i])):
            friends[i][preferences[i][j]] = j
    pairing = [0]*n
    for i, j in pairs:
        pairing[i], pairing[j] = j, i
    return sum(any(friends[i][j] < friends[i][pairing[i]] and friends[j][i] < friends[j][pairing[j]]
                   for j in xrange(len(friends[i])) if j != i and j != pairing[i])
               for i in xrange(len(friends)))


