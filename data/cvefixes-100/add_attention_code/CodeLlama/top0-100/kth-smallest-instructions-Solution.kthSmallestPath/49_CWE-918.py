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

def kthSmallestPath(self, destination, k):
    """
    :type destination: List[int]
    :type k: int
    :rtype: str
    """
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if n < r:
            return 0
        if n-r < r:
            return nCr(n, n-r)
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c

    r, c = destination        
    result = []
    while r+c:
        count = nCr(r+(c-1), r)  # the number of HX..X combinations
        if k <= count:  # the kth instruction is one of HX..X combinations, so go right
            c -= 1
            result.append('H')
        else:  # the kth instruction is one of VX..X combinations, so go down
            k -= count  # the kth one of XX..X combinations is the (k-count)th one of VX..X combinations
            r -= 1
            result.append('V')
    return "".join(result)


