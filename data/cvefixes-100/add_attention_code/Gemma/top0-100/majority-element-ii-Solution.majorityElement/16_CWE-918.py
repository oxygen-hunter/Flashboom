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

def majorityElement(self, nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    k, n, cnts = 3, len(nums), collections.defaultdict(int)

    for i in nums:
        cnts[i] += 1
        # Detecting k items in cnts, at least one of them must have exactly
        # one in it. We will discard those k items by one for each.
        # This action keeps the same mojority numbers in the remaining numbers.
        # Because if x / n  > 1 / k is true, then (x - 1) / (n - k) > 1 / k is also true.
        if len(cnts) == k:
            for j in cnts.keys():
                cnts[j] -= 1
                if cnts[j] == 0:
                    del cnts[j]

    # Resets cnts for the following counting.
    for i in cnts.keys():
        cnts[i] = 0

    # Counts the occurrence of each candidate integer.
    for i in nums:
        if i in cnts:
            cnts[i] += 1

    # Selects the integer which occurs > [n / k] times.
    result = []
    for i in cnts.keys():
        if cnts[i] > n / k:
            result.append(i)

    return result



