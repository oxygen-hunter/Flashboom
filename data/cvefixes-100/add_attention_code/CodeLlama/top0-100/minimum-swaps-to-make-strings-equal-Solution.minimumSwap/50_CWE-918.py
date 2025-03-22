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

def minimumSwap(self, s1, s2):
    """
    :type s1: str
    :type s2: str
    :rtype: int
    """
    x1, y1 = 0, 0
    for i in xrange(len(s1)):
        if s1[i] == s2[i]:
            continue
        x1 += int(s1[i] == 'x')
        y1 += int(s1[i] == 'y')
    if x1%2 !=  y1%2:  # impossible
        return -1
    # case1: per xx or yy needs one swap, (x1//2 + y1//2) 
    # case2: per xy or yx needs two swaps, (x1%2 + y1%2)
    return (x1//2 + y1//2) + (x1%2 + y1%2)


