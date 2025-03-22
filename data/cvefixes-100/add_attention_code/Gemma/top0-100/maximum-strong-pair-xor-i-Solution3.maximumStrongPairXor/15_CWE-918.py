def category_list():
    if current_user.check_visibility(constants.SIDEBAR_CATEGORY):
        if current_user.get_view_property('category', 'dir') == 'desc':
            order = db.Tags.name.desc()
            order_no = 0
        else:
            order = db.Tags.name.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Tags, func.count('books_tags_link.book').label('count')) \
            .join(db.books_tags_link).join(db.Books).order_by(order).filter(calibre_db.common_filters()) \
            .group_by(text('books_tags_link.tag')).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Tags.name, 1, 1)).label('char')) \
            .join(db.books_tags_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Tags.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Categories"), page="catlist", data="category", order=order_no)
    else:
        abort(404)

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



