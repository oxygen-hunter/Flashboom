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

def setZeroes(self, matrix):
    first_col = reduce(lambda acc, i: acc or matrix[i][0] == 0, xrange(len(matrix)), False)
    first_row = reduce(lambda acc, j: acc or matrix[0][j] == 0, xrange(len(matrix[0])), False)

    for i in xrange(1, len(matrix)):
        for j in xrange(1, len(matrix[0])):
            if matrix[i][j] == 0:
                matrix[i][0], matrix[0][j] = 0, 0

    for i in xrange(1, len(matrix)):
        for j in xrange(1, len(matrix[0])):
            if matrix[i][0] == 0 or matrix[0][j] == 0:
                matrix[i][j] = 0

    if first_col:
        for i in xrange(len(matrix)):
            matrix[i][0] = 0

    if first_row:
        for j in xrange(len(matrix[0])):
            matrix[0][j] = 0



