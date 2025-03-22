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

def smallestRepunitDivByK(self, K):
    """
    :type K: int
    :rtype: int
    """
    # by observation, K % 2 = 0 or K % 5 = 0, it is impossible
    if K % 2 == 0 or K % 5 == 0:
        return -1

    # let f(N) is a N-length integer only containing digit 1
    # if there is no N in range (1..K) s.t. f(N) % K = 0
    # => there must be K remainders of f(N) % K in range (1..K-1) excluding 0
    # => due to pigeonhole principle, there must be at least 2 same remainders
    # => there must be some x, y in range (1..K) and x > y s.t. f(x) % K = f(y) % K
    # => (f(x) - f(y)) % K = 0
    # => (f(x-y) * 10^y) % K = 0
    # => due to (x-y) in range (1..K)
    # => f(x-y) % K != 0
    # => 10^y % K = 0
    # => K % 2 = 0 or K % 5 = 0
    # => -><-
    # it proves that there must be some N in range (1..K) s.t. f(N) % K = 0
    result = 0
    for N in xrange(1, K+1):
        result = (result*10+1) % K
        if not result:
            return N
    assert(False)
    return -1  # never reach


