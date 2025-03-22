def render_downloaded_books(page, order, user_id):
    if current_user.role_admin():
        user_id = int(user_id)
    else:
        user_id = current_user.id
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD):
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()

        entries, __, pagination = calibre_db.fill_indexpage(page,
                                                            0,
                                                            db.Books,
                                                            ub.Downloads.user_id == user_id,
                                                            order[0],
                                                            False, 0,
                                                            db.books_series_link,
                                                            db.Books.id == db.books_series_link.c.book,
                                                            db.Series,
                                                            ub.Downloads, db.Books.id == ub.Downloads.book_id)
        for book in entries:
            if not calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                             .filter(db.Books.id == book.id).first():
                ub.delete_download(book.id)
        user = ub.session.query(ub.User).filter(ub.User.id == user_id).first()
        return render_title_template('index.html',
                                     random=random,
                                     entries=entries,
                                     pagination=pagination,
                                     id=user_id,
                                     title=_(u"Downloaded books by %(user)s",user=user.name),
                                     page="download",
                                     order=order[1])
    else:
        abort(404)

def minimumLines(self, points):
    """
    :type points: List[List[int]]
    :rtype: int
    """
    def gcd(a, b):  # Time: O(log(a + b))
        while b:
            a, b = b, a % b
        return a

    def popcount(x):
        result = 0
        while x:
            x &= (x-1)
            result += 1
        return result

    def ceil_divide(a, b):
        return (a+b-1)//b
    
    lookup = collections.defaultdict(set)               
    for i, (x1, y1) in enumerate(points):
        for j in xrange(i+1, len(points)):
            x2, y2 = points[j]
            # (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
            # => (y2-y1)x - (x2-x1)y = x1(y2-y1) - y1(x2-x1)
            a, b, c = (y2-y1), -(x2-x1), x1*(y2-y1)-y1*(x2-x1) 
            g = gcd(gcd(a, b), c)
            a, b, c = a//g, b//g, c//g
            lookup[(a, b, c)].add((x1, y1))
            lookup[(a, b, c)].add((x2, y2))
    lines = [l for l, p in lookup.iteritems() if len(p) > 2]  # filter to improve complexity
    assert(len(lines) <= (len(points))//2)  # 1 extra colinear point per 2 points
    result = float("inf")
    for mask in xrange(1<<len(lines)):
        covered = set()
        bit, i = 1, 0
        while bit <= mask:
            if mask&bit:
                covered.update(lookup[lines[i]])
            bit <<= 1                        
            i += 1
        result = min(result, popcount(mask) + ceil_divide(len(points)-len(covered), 2))
    return result


