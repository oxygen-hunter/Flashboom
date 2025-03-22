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

def stoneGameIX(self, stones):
    """
    :type stones: List[int]
    :rtype: bool
    """
    count = collections.Counter(x%3 for x in stones)
    if count[0]%2 == 0:
        # iff both counts are not zero, then alice takes the least one at first, the remains are deterministic for bob to lose:
        # - assumed count[1] is the least one:
        #   1(,1,2)*,2,(,2)* => bob loses
        #            ^
        # - assumed count[2] is the least one:
        #   2(,2,1)*,1,(,1)* => bob loses
        #            ^
        return count[1] and count[2]
    # iff abs(count[1] - count[2]) >= 3, then alice takes the most one at first, the remains are deterministic for bob to lose:
    # - assumed count[1] is the most one
    #   1(,1,2)*,0,1(,2,1)*,1,(,1)* => bob loses
    #                       ^
    #   1(,1,2)*,1,0,1,(,1)* => bob loses
    #                ^
    # - assumed count[2] is the most one
    #   2(,2,1)*,0,2(,1,2)*,2,(,2)* => bob loses
    #                       ^
    #   2(,2,1)*,2,0,2,(,2)* => bob loses
    #                ^
    return abs(count[1]-count[2]) >= 3  


