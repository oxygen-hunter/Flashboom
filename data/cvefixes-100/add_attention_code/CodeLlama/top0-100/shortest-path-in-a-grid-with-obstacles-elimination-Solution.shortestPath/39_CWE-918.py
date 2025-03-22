def render_adv_search_results(term, offset=None, order=None, limit=None):
    sort_param = order[0] if order else [db.Books.sort]
    pagination = None

    cc = get_cc_columns(filter_config_custom_read=True)
    calibre_db.session.connection().connection.connection.create_function("lower", 1, db.lcase)
    if not config.config_read_column:
        query = (calibre_db.session.query(db.Books, ub.ArchivedBook.is_archived, ub.ReadBook).select_from(db.Books)
                 .outerjoin(ub.ReadBook, and_(db.Books.id == ub.ReadBook.book_id,
                                              int(current_user.id) == ub.ReadBook.user_id)))
    else:
        try:
            read_column = cc[config.config_read_column]
            query = (calibre_db.session.query(db.Books, ub.ArchivedBook.is_archived, read_column.value)
                     .select_from(db.Books)
                     .outerjoin(read_column, read_column.book == db.Books.id))
        except (KeyError, AttributeError):
            log.error("Custom Column No.%d is not existing in calibre database", config.config_read_column)
            # Skip linking read column
            query = calibre_db.session.query(db.Books, ub.ArchivedBook.is_archived, None)
    query = query.outerjoin(ub.ArchivedBook, and_(db.Books.id == ub.ArchivedBook.book_id,
                                                  int(current_user.id) == ub.ArchivedBook.user_id))

    q = query.outerjoin(db.books_series_link, db.Books.id == db.books_series_link.c.book)\
        .outerjoin(db.Series)\
        .filter(calibre_db.common_filters(True))

    # parse multiselects to a complete dict
    tags = dict()
    elements = ['tag', 'serie', 'shelf', 'language', 'extension']
    for element in elements:
        tags['include_' + element] = term.get('include_' + element)
        tags['exclude_' + element] = term.get('exclude_' + element)

    author_name = term.get("author_name")
    book_title = term.get("book_title")
    publisher = term.get("publisher")
    pub_start = term.get("publishstart")
    pub_end = term.get("publishend")
    rating_low = term.get("ratinghigh")
    rating_high = term.get("ratinglow")
    description = term.get("comment")
    read_status = term.get("read_status")
    if author_name:
        author_name = author_name.strip().lower().replace(',', '|')
    if book_title:
        book_title = book_title.strip().lower()
    if publisher:
        publisher = publisher.strip().lower()

    searchterm = []
    cc_present = False
    for c in cc:
        if c.datatype == "datetime":
            column_start = term.get('custom_column_' + str(c.id) + '_start')
            column_end = term.get('custom_column_' + str(c.id) + '_end')
            if column_start:
                searchterm.extend([u"{} >= {}".format(c.name,
                                                      format_date(datetime.strptime(column_start, "%Y-%m-%d").date(),
                                                                      format='medium',
                                                                      locale=get_locale())
                                                      )])
                cc_present = True
            if column_end:
                searchterm.extend([u"{} <= {}".format(c.name,
                                                      format_date(datetime.strptime(column_end, "%Y-%m-%d").date(),
                                                                      format='medium',
                                                                      locale=get_locale())
                                                      )])
                cc_present = True
        elif term.get('custom_column_' + str(c.id)):
            searchterm.extend([(u"{}: {}".format(c.name, term.get('custom_column_' + str(c.id))))])
            cc_present = True


    if any(tags.values()) or author_name or book_title or publisher or pub_start or pub_end or rating_low \
       or rating_high or description or cc_present or read_status:
        searchterm, pub_start, pub_end = extend_search_term(searchterm,
                                                            author_name,
                                                            book_title,
                                                            publisher,
                                                            pub_start,
                                                            pub_end,
                                                            tags,
                                                            rating_high,
                                                            rating_low,
                                                            read_status)
        # q = q.filter()
        if author_name:
            q = q.filter(db.Books.authors.any(func.lower(db.Authors.name).ilike("%" + author_name + "%")))
        if book_title:
            q = q.filter(func.lower(db.Books.title).ilike("%" + book_title + "%"))
        if pub_start:
            q = q.filter(func.datetime(db.Books.pubdate) > func.datetime(pub_start))
        if pub_end:
            q = q.filter(func.datetime(db.Books.pubdate) < func.datetime(pub_end))
        q = adv_search_read_status(q, read_status)
        if publisher:
            q = q.filter(db.Books.publishers.any(func.lower(db.Publishers.name).ilike("%" + publisher + "%")))
        q = adv_search_tag(q, tags['include_tag'], tags['exclude_tag'])
        q = adv_search_serie(q, tags['include_serie'], tags['exclude_serie'])
        q = adv_search_shelf(q, tags['include_shelf'], tags['exclude_shelf'])
        q = adv_search_extension(q, tags['include_extension'], tags['exclude_extension'])
        q = adv_search_language(q, tags['include_language'], tags['exclude_language'])
        q = adv_search_ratings(q, rating_high, rating_low)

        if description:
            q = q.filter(db.Books.comments.any(func.lower(db.Comments.text).ilike("%" + description + "%")))

        # search custom culumns
        try:
            q = adv_search_custom_columns(cc, term, q)
        except AttributeError as ex:
            log.error_or_exception(ex)
            flash(_("Error on search for custom columns, please restart Calibre-Web"), category="error")

    q = q.order_by(*sort_param).all()
    flask_session['query'] = json.dumps(term)
    ub.store_combo_ids(q)
    result_count = len(q)
    if offset is not None and limit is not None:
        offset = int(offset)
        limit_all = offset + int(limit)
        pagination = Pagination((offset / (int(limit)) + 1), limit, result_count)
    else:
        offset = 0
        limit_all = result_count
    entries = calibre_db.order_authors(q[offset:limit_all], list_return=True, combined=True)
    return render_title_template('search.html',
                                 adv_searchterm=searchterm,
                                 pagination=pagination,
                                 entries=entries,
                                 result_count=result_count,
                                 title=_(u"Advanced Search"), page="advsearch",
                                 order=order[1])

def shortestPath(self, grid, k):
    """
    :type grid: List[List[int]]
    :type k: int
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def dot(a, b):
        return a[0]*b[0]+a[1]*b[1]

    def g(a, b):
        return abs(a[0]-b[0])+abs(a[1]-b[1])
    
    def a_star(grid, b, t, k):
        f, dh = g(b, t), 2
        closer, detour = [(b, k)], []
        lookup = {}
        while closer or detour:
            if not closer:
                f += dh
                closer, detour = detour, closer
            b, k = closer.pop()
            if b == t:
                return f
            if b in lookup and lookup[b] >= k:
                continue
            lookup[b] = k
            for dx, dy in directions:
                nb = (b[0]+dx, b[1]+dy)
                if not (0 <= nb[0] < len(grid) and 0 <= nb[1] < len(grid[0]) and
                        (grid[nb[0]][nb[1]] == 0 or k > 0) and
                        (nb not in lookup or lookup[nb] < k)):
                    continue
                (closer if dot((dx, dy), (t[0]-b[0], t[1]-b[1])) > 0 else detour).append((nb, k-int(grid[nb[0]][nb[1]] == 1)))
        return -1

    return a_star(grid, (0, 0), (len(grid)-1, len(grid[0])-1), k)


