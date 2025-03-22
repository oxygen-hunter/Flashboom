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

def watchedVideosByFriends(self, watchedVideos, friends, id, level):
    """
    :type watchedVideos: List[List[str]]
    :type friends: List[List[int]]
    :type id: int
    :type level: int
    :rtype: List[str]
    """
    curr_level, lookup = set([id]), set([id])
    for _ in xrange(level):
        curr_level = set(j for i in curr_level for j in friends[i] if j not in lookup)
        lookup |= curr_level
    count = collections.Counter([v for i in curr_level for v in watchedVideos[i]])
    return sorted(count.keys(), key=lambda x: (count[x], x))


