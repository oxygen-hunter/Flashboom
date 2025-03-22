def series_list():
    if current_user.check_visibility(constants.SIDEBAR_SERIES):
        if current_user.get_view_property('series', 'dir') == 'desc':
            order = db.Series.sort.desc()
            order_no = 0
        else:
            order = db.Series.sort.asc()
            order_no = 1
        if current_user.get_view_property('series', 'series_view') == 'list':
            entries = calibre_db.session.query(db.Series, func.count('books_series_link.book').label('count')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(text('books_series_link.series')).order_by(order).all()
            charlist = calibre_db.session.query(func.upper(func.substr(db.Series.sort, 1, 1)).label('char')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(func.upper(func.substr(db.Series.sort, 1, 1))).all()
            return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                         title=_(u"Series"), page="serieslist", data="series", order=order_no)
        else:
            entries = calibre_db.session.query(db.Books, func.count('books_series_link').label('count'),
                                               func.max(db.Books.series_index), db.Books.id) \
                .join(db.books_series_link).join(db.Series).filter(calibre_db.common_filters())\
                .group_by(text('books_series_link.series')).order_by(order).all()
            charlist = calibre_db.session.query(func.upper(func.substr(db.Series.sort, 1, 1)).label('char')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(func.upper(func.substr(db.Series.sort, 1, 1))).all()

            return render_title_template('grid.html', entries=entries, folder='web.books_list', charlist=charlist,
                                         title=_(u"Series"), page="serieslist", data="series", bodyClass="grid-view",
                                         order=order_no)
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


