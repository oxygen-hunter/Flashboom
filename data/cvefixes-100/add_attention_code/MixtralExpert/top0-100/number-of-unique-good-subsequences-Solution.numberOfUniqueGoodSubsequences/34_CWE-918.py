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

def numberOfUniqueGoodSubsequences(self, binary):
    """
    :type binary: str
    :rtype: int
    """
    MOD = 10**9+7
    ends0, ends1 = 0, 0
    has_zero = False
    for b in binary:
        if b == '1':
            ends1 = (ends0+ends1+1)%MOD  # curr subsequences end with 1 is all prev distinct subsequences appended by 1 and plus "1"
        else:
            ends0 = (ends0+ends1)%MOD  # curr subsequences end with 0 is all prev distinct subsequences appended by 0 and don't plus "0"
            has_zero = True
    return (ends0+ends1+int(has_zero))%MOD  # add "0" if has_zero


