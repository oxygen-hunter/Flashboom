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

def maxNiceDivisors(self, primeFactors):
    """
    :type primeFactors: int
    :rtype: int
    """
    # given a1 + a2 + ... + ak <= n, find max of a1 * a2 * ... * ak 
    # => given a1 + a2 + ... + ak = n, find max of a1 * a2 * ... * ak 
    # => ai is either 3 or 2, see proof in "343. integer break"
    MOD = 10**9 + 7
    if primeFactors <= 3:
        return primeFactors
    if primeFactors % 3 == 0:  # 6 => 3*3
        return pow(3, primeFactors//3, MOD)
    if primeFactors % 3 == 1:  # 4 => 2*2 
        return (2*2*pow(3, (primeFactors-4)//3, MOD)) % MOD
    return (2*pow(3, (primeFactors-2)//3, MOD)) % MOD  # 5 => 2*3


