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


