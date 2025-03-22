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

def findGoodStrings(self, n, s1, s2, evil):
    """
    :type n: int
    :type s1: str
    :type s2: str
    :type evil: str
    :rtype: int
    """
    MOD = 10**9+7
    def getPrefix(pattern):
        prefix = [-1]*len(pattern)
        j = -1
        for i in xrange(1, len(pattern)):
            while j != -1 and pattern[j+1] != pattern[i]:
                j = prefix[j]
            if pattern[j+1] == pattern[i]:
                j += 1
            prefix[i] = j
        return prefix

    prefix = getPrefix(evil)
    dp = [[[[0]*len(evil) for _ in xrange(2)] for _ in xrange(2)] for _ in xrange(2)]
    dp[0][0][0][0] = 1
    for i in xrange(n):
        dp[(i+1)%2] = [[[0]*len(evil) for _ in xrange(2)] for _ in xrange(2)]
        for j in xrange(2):
            for k in xrange(2):
                min_c = 'a' if j else s1[i]
                max_c = 'z' if k else s2[i]
                for l in xrange(len(evil)):
                    if not dp[i%2][j][k][l]:
                        continue
                    for c in xrange(ord(min_c)-ord('a'), ord(max_c)-ord('a')+1):
                        c = chr(c+ord('a'))
                        m = l-1
                        while m != -1 and evil[m+1] != c:
                            m = prefix[m]
                        if evil[m+1] == c:
                            m += 1
                        if m+1 == len(evil):
                            continue
                        dp[(i+1)%2][j or (s1[i] != c)][k or (s2[i] != c)][m+1] = \
                            (dp[(i+1)%2][j or (s1[i] != c)][k or (s2[i] != c)][m+1] + dp[i%2][j][k][l]) % MOD
    result = 0
    for j in xrange(2):
        for k in xrange(2):
            for l in xrange(len(evil)):
                result = (result + dp[n%2][j][k][l]) % MOD
    return result


