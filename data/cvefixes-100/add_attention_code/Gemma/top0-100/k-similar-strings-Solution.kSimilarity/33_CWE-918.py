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

def kSimilarity(self, A, B):
    """
    :type A: str
    :type B: str
    :rtype: int
    """
    def neighbors(s, B):
        for i, c in enumerate(s):
            if c != B[i]:
                break
        t = list(s)
        for j in xrange(i+1, len(s)):
            if t[j] == B[i]:
                t[i], t[j] = t[j], t[i]
                yield "".join(t)
                t[j], t[i] = t[i], t[j]

    q = collections.deque([A])
    lookup = set()
    result = 0
    while q:
        for _ in xrange(len(q)):
            s = q.popleft()
            if s == B:
                return result
            for t in neighbors(s, B):
                if t not in lookup:
                    lookup.add(t)
                    q.append(t)
        result += 1



