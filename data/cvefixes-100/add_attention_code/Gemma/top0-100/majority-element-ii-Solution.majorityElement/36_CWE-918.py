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



