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

def minCostToEqualizeArray(self, nums, cost1, cost2):
    """
    :type nums: List[int]
    :type cost1: int
    :type cost2: int
    :rtype: int
    """
    MOD = 10**9+7

    n = len(nums)
    mx = max(nums)
    total = mx*n-sum(nums)

    # fill until mx with only cost1 operations
    if n <= 2 or cost1*2 <= cost2:
        return total*cost1%MOD

    result = float("inf")
    # fill until mx with more cost2 operations and fewer cost1 operations
    mn = min(nums)
    cnt1 = max((mx-mn)-(total-(mx-mn)), 0)
    cnt2 = total-cnt1
    result = min(result, (cnt1+cnt2%2)*cost1 + cnt2//2*cost2)

    # fill until mx+x with most cost2 operations and fewest cost1 operations,
    # where x is the  max of x s.t. cnt1+x >= (n-1)*x => cnt1 >= (n-2)*x
    x, cnt1 = divmod(cnt1, (n-2))
    total += n*x
    cnt2 = total-cnt1
    result = min(result, (cnt1+cnt2%2)*cost1 + (cnt2//2)*cost2)

    # fill until mx+x+1 or mx+x+2 with nearly all cost2 operations and at most one cost1 operation
    for _ in xrange(2):  # increase twice is for odd n
        total += n
        result = min(result, total%2*cost1 + total//2*cost2)
    return result%MOD


