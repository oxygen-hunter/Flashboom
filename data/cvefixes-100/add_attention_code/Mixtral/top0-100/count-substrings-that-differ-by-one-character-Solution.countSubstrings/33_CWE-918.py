def publisher_list():
    if current_user.get_view_property('publisher', 'dir') == 'desc':
        order = db.Publishers.name.desc()
        order_no = 0
    else:
        order = db.Publishers.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_PUBLISHER):
        entries = calibre_db.session.query(db.Publishers, func.count('books_publishers_link.book').label('count')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_publishers_link.publisher')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Publishers.name, 1, 1)).label('char')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Publishers.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Publishers"), page="publisherlist", data="publisher", order=order_no)
    else:
        abort(404)

def countSubstrings(self, s, t):
    """
    :type s: str
    :type t: str
    :rtype: int
    """
    def count(i, j):  # for each possible alignment, count the number of substrs that differ by 1 char
        result = left_cnt = right_cnt = 0  # left and right consecutive same counts relative to the different char
        for k in xrange(min(len(s)-i, len(t)-j)):
            right_cnt += 1
            if s[i+k] != t[j+k]:
                left_cnt, right_cnt = right_cnt, 0
                # prev_i = i+k-prev+1
            result += left_cnt  # target substrs are [s[left_i+c:i+k+1] for c in xrange(left_cnt)]
        return result

    return sum(count(i, 0) for i in xrange(len(s))) + \
           sum(count(0, j) for j in xrange(1, len(t)))


