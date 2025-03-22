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

def timeTaken(self, arrival, state):
    """
    :type arrival: List[int]
    :type state: List[int]
    :rtype: List[int]
    """
    def go_until(t):
        while curr[0] <= t and any(q):
            if not q[direction[0]]:
                direction[0] ^= 1
            result[q[direction[0]].popleft()] = curr[0]
            curr[0] += 1

    UNKNOWN, ENTERING, EXITING = range(-1, 1+1)
    result = [0]*len(arrival)
    curr, direction = [float("-inf")], [UNKNOWN]
    q = [collections.deque(), collections.deque()]
    for i, (a, s) in enumerate(itertools.izip(arrival, state)):
        go_until(a-1)
        q[s].append(i)
        if not (a <= curr[0]):
            curr, direction = [a], [EXITING]
    go_until(float("inf"))
    return result


