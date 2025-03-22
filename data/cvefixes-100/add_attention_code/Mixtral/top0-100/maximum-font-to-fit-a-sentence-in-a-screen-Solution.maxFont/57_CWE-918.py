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

def maxFont(self, text, w, h, fonts, fontInfo):
    """
    :type text: str
    :type w: int
    :type h: int
    :type fonts: List[int]
    :type fontInfo: FontInfo
    :rtype: int
    """
    def check(count, w, h, fonts, fontInfo, x):  # Time: O(1)
        return (fontInfo.getHeight(fonts[x]) <= h and
                sum(cnt * fontInfo.getWidth(fonts[x], c) for c, cnt in count.iteritems()) <= w)

    count = collections.Counter(text)
    left, right = 0, len(fonts)-1
    while left <= right:
        mid = left + (right-left)//2
        if not check(count, w, h, fonts, fontInfo, mid):
            right = mid-1
        else:
            left = mid+1
    return fonts[right] if right >= 0 else -1


