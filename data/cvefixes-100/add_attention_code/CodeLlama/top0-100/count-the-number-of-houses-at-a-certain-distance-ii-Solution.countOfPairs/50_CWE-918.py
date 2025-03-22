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

def countOfPairs(self, n, x, y):
    """
    :type n: int
    :type x: int
    :type y: int
    :rtype: List[int]
    """
    x, y = x-1, y-1
    if x > y:
        x, y = y, x
    diff = [0]*n
    for i in xrange(n):
        diff[0] += 1+1                                         # i -> two routes begin
        diff[min(abs(i-x), abs(i-y)+1)] += 1                   # i -> x -> y, fork one route at x to y
        diff[min(abs(i-y), abs(i-x)+1)] += 1                   # i -> y -> x, fork one route at y to x
        diff[min(abs(i-0), abs(i-y)+1+abs(x-0))] -= 1          # i -> 0, one route ends
        diff[min(abs(i-(n-1)), abs(i-x)+1+abs(y-(n-1)))] -= 1  # i -> n-1, one route ends
        diff[max(x-i, 0)+max(i-y, 0)+((y-x)+0)//2] -= 1        # i -> x -> ((y-x)+0)//2 <- x, one route ends
        diff[max(x-i, 0)+max(i-y, 0)+((y-x)+1)//2] -= 1        # i -> y -> ((y-x)+1)//2 <- y, one route ends
    for i in xrange(n-1):
        diff[i+1] += diff[i]
    return diff


