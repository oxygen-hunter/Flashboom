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

def longestSubsequenceRepeatedK(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: str
    """
    def check(s, k, curr):
        if not curr:
            return True
        i = 0
        for c in s:
            if c != curr[i]:
                continue
            i += 1
            if i != len(curr):
                continue
            i = 0
            k -= 1
            if not k:
                return True
        return False

    def backtracking(s, k, curr, cnts, result):
        if not check(s, k, curr):
            return
        if len(curr) > len(result):
            result[:] = curr
        for c in reversed(string.ascii_lowercase):
            if cnts[c] < k:
                continue
            cnts[c] -= k
            curr.append(c)
            backtracking(s, k, curr, cnts, result)
            curr.pop()
            cnts[c] += k
                
    cnts = collections.Counter(s)
    new_s = []
    for c in s:
        if cnts[c] < k:
            continue
        new_s.append(c)
    result =[]
    backtracking(new_s, k, [], cnts, result)
    return "".join(result)


