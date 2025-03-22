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

def buildWall(self, height, width, bricks):
    """
    :type height: int
    :type width: int
    :type bricks: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    def backtracking(height, width, bricks, total, mask, lookup, patterns):
        if mask in lookup:
            return
        lookup.add(mask)
        if total >= width:
            if total == width:
                patterns.append(mask^(1<<width))
            return
        for x in bricks:
            backtracking(height, width, bricks, total+x, mask|(1<<(total+x)), lookup, patterns)

    def matrix_mult(A, B):
        ZB = zip(*B)
        return [[sum(a*b % MOD for a, b in itertools.izip(row, col)) % MOD for col in ZB] for row in A]
 
    def matrix_expo(A, K):
        result = [[int(i == j) for j in xrange(len(A))] for i in xrange(len(A))]
        while K:
            if K % 2:
                result = matrix_mult(result, A)
            A = matrix_mult(A, A)
            K /= 2
        return result

    patterns, lookup = [], set()
    backtracking(height, width, bricks, 0, 0, lookup, patterns)
    return reduce(lambda x,y: (x+y)%MOD,
                  matrix_mult([[1]*len(patterns)],
                               matrix_expo([[int((mask1 & mask2) == 0)
                                             for mask2 in patterns] 
                                             for mask1 in patterns], height-1))[0],
                  0)  # Time: O(p^3 * logh), Space: O(p^2)


