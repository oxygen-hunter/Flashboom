def ratings_list():
    if current_user.check_visibility(constants.SIDEBAR_RATING):
        if current_user.get_view_property('ratings', 'dir') == 'desc':
            order = db.Ratings.rating.desc()
            order_no = 0
        else:
            order = db.Ratings.rating.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Ratings, func.count('books_ratings_link.book').label('count'),
                                   (db.Ratings.rating / 2).label('name')) \
            .join(db.books_ratings_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_ratings_link.rating')).order_by(order).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=list(),
                                     title=_(u"Ratings list"), page="ratingslist", data="ratings", order=order_no)
    else:
        abort(404)

def minimumCost(self, nums, k, dist):
    """
    :type nums: List[int]
    :type k: int
    :type dist: int
    :rtype: int
    """
    sl1, sl2 = SortedList(), SortedList()
    mn, curr = float("inf"), 0
    for i in xrange(1, len(nums)):
        sl1.add(nums[i])
        curr += nums[i]
        if len(sl1) > k-1:
            curr -= sl1[-1]
            sl2.add(sl1.pop())
        if len(sl1)+len(sl2) > 1+dist:
            if sl2[0] <= nums[i-(1+dist)]:
                sl2.remove(nums[i-(1+dist)])
            else:
                sl1.remove(nums[i-(1+dist)])
                curr -= nums[i-(1+dist)]-sl2[0]
                sl1.add(sl2.pop(0))
        if len(sl1) == k-1:
            mn = min(mn, curr)
    return nums[0]+mn



