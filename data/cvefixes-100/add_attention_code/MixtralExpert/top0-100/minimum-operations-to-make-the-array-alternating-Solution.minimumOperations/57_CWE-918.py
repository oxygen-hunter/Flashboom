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

def minimumOperations(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    even_top = collections.Counter(nums[i] for i in xrange(0, len(nums), 2)).most_common(2)  # Time: O(nlogk)
    odd_top = collections.Counter(nums[i] for i in xrange(1, len(nums), 2)).most_common(2)  # Time: O(nlogk)
    if not odd_top or even_top[0][0] != odd_top[0][0]:
        return len(nums)-even_top[0][1]-(odd_top[0][1] if odd_top else 0)
    return min(len(nums)-even_top[0][1]-(odd_top[1][1] if len(odd_top) == 2 else 0),
               len(nums)-odd_top[0][1]-(even_top[1][1] if len(even_top) == 2 else 0))


