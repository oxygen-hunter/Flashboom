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

def maxSumRangeQuery(self, nums, requests):
    """
    :type nums: List[int]
    :type requests: List[List[int]]
    :rtype: int
    """
    def addmod(a, b, mod):  # avoid overflow in other languages
        a %= mod
        b %= mod
        if mod-a <= b:
            b -= mod
        return a+b
    
    def mulmod(a, b, mod):  # avoid overflow in other languages
        a %= mod
        b %= mod
        if a < b:
            a, b = b, a
        result = 0
        while b > 0:
            if b%2 == 1:
                result = addmod(result, a, mod)
            a = addmod(a, a, mod)
            b //= 2
        return result

    MOD = 10**9+7

    count = [0]*len(nums)
    for start, end in requests:
        count[start] += 1
        if end+1 < len(count):
            count[end+1] -= 1
    for i in xrange(1, len(count)):
        count[i] += count[i-1]
    nums.sort()
    count.sort()
    result = 0
    for i, (num, c) in enumerate(itertools.izip(nums, count)):
        # result = addmod(result, mulmod(num, c, MOD), MOD)
        result = (result+num*c)%MOD
    return result


