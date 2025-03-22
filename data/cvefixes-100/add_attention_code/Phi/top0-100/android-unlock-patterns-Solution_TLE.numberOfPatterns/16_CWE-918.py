def category_list():
    if current_user.check_visibility(constants.SIDEBAR_CATEGORY):
        if current_user.get_view_property('category', 'dir') == 'desc':
            order = db.Tags.name.desc()
            order_no = 0
        else:
            order = db.Tags.name.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Tags, func.count('books_tags_link.book').label('count')) \
            .join(db.books_tags_link).join(db.Books).order_by(order).filter(calibre_db.common_filters()) \
            .group_by(text('books_tags_link.tag')).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Tags.name, 1, 1)).label('char')) \
            .join(db.books_tags_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Tags.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Categories"), page="catlist", data="category", order=order_no)
    else:
        abort(404)

def numberOfPatterns(self, m, n):
    """
    :type m: int
    :type n: int
    :rtype: int
    """
    def merge(used, i):
        return used | (1 << i)

    def contain(used, i):
        return bool(used & (1 << i))

    def convert(i, j):
        return 3 * i + j

    def numberOfPatternsHelper(m, n, level, used, i):
        number = 0
        if level > n:
            return number

        if m <= level <= n:
            number += 1

        x1, y1 = divmod(i, 3)
        for j in xrange(9):
            if contain(used, j):
                continue

            x2, y2 = divmod(j, 3)
            if ((x1 == x2 and abs(y1 - y2) == 2) or
                (y1 == y2 and abs(x1 - x2) == 2) or
                (abs(x1 - x2) == 2 and abs(y1 - y2) == 2)) and \
               not contain(used,
                           convert((x1 + x2) // 2, (y1 + y2) // 2)):
                    continue

            number += numberOfPatternsHelper(m, n, level + 1, merge(used, j), j)

        return number

    number = 0
    # 1, 3, 7, 9
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 0), 0)
    # 2, 4, 6, 8
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 1), 1)
    # 5
    number += numberOfPatternsHelper(m, n, 1, merge(0, 4), 4)
    return number



