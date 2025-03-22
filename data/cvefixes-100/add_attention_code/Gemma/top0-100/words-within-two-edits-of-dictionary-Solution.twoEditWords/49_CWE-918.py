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

def twoEditWords(self, queries, dictionary):
    """
    :type queries: List[str]
    :type dictionary: List[str]
    :rtype: List[str]
    """
    MOD = (1<<64)-59  # largest 64-bit prime
    BASE = 113
    POW = [1]
    def add(a, b):
        return (a+b)%MOD

    def mult(a, b):
        return (a*b)%MOD

    def pow(i):
        while not (i < len(POW)):
            POW.append(mult(POW[-1], BASE))
        return POW[i]

    lookup = set()
    for w in dictionary:
        h = reduce(lambda h, i: add(h, mult(ord(w[i])-ord('a'), pow(i))), xrange(len(w)), 0)
        for i, c in enumerate(w):
            for x in string.ascii_lowercase:
                if x == c:
                    continue
                lookup.add(add(h, mult(ord(x)-ord(c), pow(i))))
    result = []
    for w in queries:
        h = reduce(lambda h, i: add(h, mult(ord(w[i])-ord('a'), pow(i))), xrange(len(w)), 0)
        for i, c in enumerate(w):
            for x in string.ascii_lowercase:
                if x == c:
                    continue
                if add(h, mult(ord(x)-ord(c), pow(i))) in lookup:
                    break
            else:
                continue
            result.append(w)
            break
    return result



