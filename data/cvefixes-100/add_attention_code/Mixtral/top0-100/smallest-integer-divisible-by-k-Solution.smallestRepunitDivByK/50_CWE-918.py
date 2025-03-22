def render_prepare_search_form(cc):
    # prepare data for search-form
    tags = calibre_db.session.query(db.Tags)\
        .join(db.books_tags_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_tags_link.tag'))\
        .order_by(db.Tags.name).all()
    series = calibre_db.session.query(db.Series)\
        .join(db.books_series_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_series_link.series'))\
        .order_by(db.Series.name)\
        .filter(calibre_db.common_filters()).all()
    shelves = ub.session.query(ub.Shelf)\
        .filter(or_(ub.Shelf.is_public == 1, ub.Shelf.user_id == int(current_user.id)))\
        .order_by(ub.Shelf.name).all()
    extensions = calibre_db.session.query(db.Data)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(db.Data.format)\
        .order_by(db.Data.format).all()
    if current_user.filter_language() == u"all":
        languages = calibre_db.speaking_language()
    else:
        languages = None
    return render_title_template('search_form.html', tags=tags, languages=languages, extensions=extensions,
                                 series=series,shelves=shelves, title=_(u"Advanced Search"), cc=cc, page="advsearch")

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


