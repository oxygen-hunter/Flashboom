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

def canAliceWin(self, a, b):
    """
    :type a: List[str]
    :type b: List[str]
    :rtype: bool
    """
    def is_closely_greater(a, b):
        return ord(a[0])-ord(b[0]) <= 1 and a > b

    result = True
    i, j = 0, -1
    for _ in xrange(len({w[0] for w in a})+len({w[0] for w in b})):  # each player takes turns using a word with a different first letter than the last word he played
        j = next((j for j in xrange(j+1, len(b)) if is_closely_greater(b[j], a[i])), len(b))
        if j == len(b):
            break
        while j+1 < len(b) and b[j+1][0] == b[j][0]:  # play the lexicographically greatest word with the same first letter
            j += 1
        a, b, i, j, result = b, a, j, i, not result
    return result


