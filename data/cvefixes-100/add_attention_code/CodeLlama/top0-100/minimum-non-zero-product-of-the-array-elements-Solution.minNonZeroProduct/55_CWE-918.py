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

def minNonZeroProduct(self, p):
    """
    :type p: int
    :rtype: int
    """
    MOD = 10**9+7

    # max_num = 2^p-1
    max_num_mod = (pow(2, p, MOD)-1)%MOD  # max_num % MOD

    # pair_product = max_num-1
    pair_product_mod = (max_num_mod-1)%MOD  # (max_num_mod-1) % MOD

    # since pair_product^MOD % MOD = pair_product_mod^MOD % MOD  = pair_product_mod
    # => pair_product_mod^(MOD-1) % MOD = 1
    # => pair_product_mod^(pair_cnt) % MOD = pair_product_mod^(pair_cnt%(MOD-1)) %MOD
    pair_cnt_mod_m_1 = (pow(2, p-1, MOD-1)-1) % (MOD-1)  # pair_cnt%(MOD-1)

    # the ans is:
    #   max_num * pair_product^pair_cnt % MOD
    # = max_num_mod * pair_product_mod^(pair_cnt_mod_m_1) % MOD
    return (max_num_mod*pow(pair_product_mod, pair_cnt_mod_m_1, MOD)) % MOD


