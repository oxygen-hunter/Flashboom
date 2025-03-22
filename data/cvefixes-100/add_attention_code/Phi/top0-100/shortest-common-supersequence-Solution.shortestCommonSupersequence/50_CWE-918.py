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

def shortestCommonSupersequence(self, str1, str2):
    """
    :type str1: str
    :type str2: str
    :rtype: str
    """
    dp = [[0 for _ in xrange(len(str2)+1)] for _ in xrange(2)]
    bt = [[None for _ in xrange(len(str2)+1)] for _ in xrange(len(str1)+1)]
    for i, c in enumerate(str1):
        bt[i+1][0] = (i, 0, c)
    for j, c in enumerate(str2):
        bt[0][j+1] = (0, j, c)
    for i in xrange(len(str1)):
        for j in xrange(len(str2)):
            if dp[i % 2][j+1] > dp[(i+1) % 2][j]:
                dp[(i+1) % 2][j+1] = dp[i % 2][j+1]
                bt[i+1][j+1] = (i, j+1, str1[i])
            else:
                dp[(i+1) % 2][j+1] = dp[(i+1) % 2][j]
                bt[i+1][j+1] = (i+1, j, str2[j])
            if str1[i] != str2[j]:
                continue
            if dp[i % 2][j]+1 > dp[(i+1) % 2][j+1]:
                dp[(i+1) % 2][j+1] = dp[i % 2][j]+1
                bt[i+1][j+1] = (i, j, str1[i])
    
    i, j = len(str1), len(str2)
    result = []
    while i != 0 or j != 0:
        i, j, c = bt[i][j]
        result.append(c)
    result.reverse()
    return "".join(result)


