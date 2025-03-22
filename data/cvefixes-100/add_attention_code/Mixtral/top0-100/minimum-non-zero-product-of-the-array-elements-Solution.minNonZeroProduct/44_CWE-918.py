def render_books_list(data, sort_param, book_id, page):
    order = get_sort_function(sort_param, data)
    if data == "rated":
        return render_rated_books(page, book_id, order=order)
    elif data == "discover":
        return render_discover_books(page, book_id)
    elif data == "unread":
        return render_read_books(page, False, order=order)
    elif data == "read":
        return render_read_books(page, True, order=order)
    elif data == "hot":
        return render_hot_books(page, order)
    elif data == "download":
        return render_downloaded_books(page, order, book_id)
    elif data == "author":
        return render_author_books(page, book_id, order)
    elif data == "publisher":
        return render_publisher_books(page, book_id, order)
    elif data == "series":
        return render_series_books(page, book_id, order)
    elif data == "ratings":
        return render_ratings_books(page, book_id, order)
    elif data == "formats":
        return render_formats_books(page, book_id, order)
    elif data == "category":
        return render_category_books(page, book_id, order)
    elif data == "language":
        return render_language_books(page, book_id, order)
    elif data == "archived":
        return render_archived_books(page, order)
    elif data == "search":
        term = (request.args.get('query') or '')
        offset = int(int(config.config_books_per_page) * (page - 1))
        return render_search_results(term, offset, order, config.config_books_per_page)
    elif data == "advsearch":
        term = json.loads(flask_session['query'])
        offset = int(int(config.config_books_per_page) * (page - 1))
        return render_adv_search_results(term, offset, order, config.config_books_per_page)
    else:
        website = data or "newest"
        entries, random, pagination = calibre_db.fill_indexpage(page, 0, db.Books, True, order[0],
        														False, 0,
                                                                db.books_series_link,
                                                                db.Books.id == db.books_series_link.c.book,
                                                                db.Series)
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=_(u"Books"), page=website, order=order[1])

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


