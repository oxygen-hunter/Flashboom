def publisher_list():
    if current_user.get_view_property('publisher', 'dir') == 'desc':
        order = db.Publishers.name.desc()
        order_no = 0
    else:
        order = db.Publishers.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_PUBLISHER):
        entries = calibre_db.session.query(db.Publishers, func.count('books_publishers_link.book').label('count')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_publishers_link.publisher')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Publishers.name, 1, 1)).label('char')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Publishers.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Publishers"), page="publisherlist", data="publisher", order=order_no)
    else:
        abort(404)

def maxCompatibilitySum(self, students, mentors):
    """
    :type students: List[List[int]]
    :type mentors: List[List[int]]
    :rtype: int
    """
    def popcount(n):  # Time: O(logn) ~= O(1) if n is a 32-bit number
        result = 0
        while n:
            n &= n-1
            result += 1
        return result

    def masks(vvi):
        result = []
        for vi in vvi:
            mask, bit = 0, 1
            for i in xrange(len(vi)):
                if vi[i]:
                    mask |= bit
                bit <<= 1
            result.append(mask)
        return result

    nums1, nums2 = masks(students), masks(mentors)
    dp = [(0, 0)]*(2**len(nums2))
    for mask in xrange(len(dp)):
        bit = 1
        for i in xrange(len(nums2)):
            if (mask&bit) == 0:
                dp[mask|bit] = max(dp[mask|bit], (dp[mask][0]+(len(students[0])-popcount(nums1[dp[mask][1]]^nums2[i])), dp[mask][1]+1))
            bit <<= 1
    return dp[-1][0]


