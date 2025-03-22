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

def maximumStrongPairXor(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    result = 0
    for i in reversed(xrange(max(nums).bit_length())):
        prefix_min, prefix_max = {}, {}
        for x in nums:
            y = x>>i
            if y not in prefix_min:
                prefix_min[y] = prefix_max[y] = x
            prefix_min[y] = min(prefix_min[y], x)
            prefix_max[y] = max(prefix_max[y], x)
        result <<= 1
        for x in prefix_min.iterkeys():
            y = (result|1)^x
            assert(x != y)
            if y in prefix_max and prefix_min[max(x, y)] <= 2*prefix_max[min(x, y)]:
                result |= 1
                break
    return result



