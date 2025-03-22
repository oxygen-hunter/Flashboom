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

def confusingNumberII(self, n):
    """
    :type n: int
    :rtype: int
    """
    lookup = {"0":"0", "1":"1", "6":"9", "8":"8", "9":"6"}
    centers = {"0":"0", "1":"1", "8":"8"}
    def totalCount(n):  # count all numbers in the pattern of [01689]{1,len(n)} in the range of [0, n]
        s = str(n)
        total = 0 
        p = len(lookup)**(len(s)-1)
        for i in xrange(len(s)+1):
            if i == len(s):
                total += 1
                break
            smaller = sum(int(c < s[i]) for c in lookup.iterkeys())
            total += smaller * p
            if s[i] not in lookup:
                break
            p //= len(lookup)
        return total

    def validCountInLessLength(n):  # count unconfusing numbers in the pattern of [01689]{1,len(n)-1} in the range of [0, n]
        s = str(n)
        valid = 0
        total = len(centers)
        for i in xrange(1, len(s), 2):  # count unconfusing numbers for each odd length less than s
            if i == 1:
                valid += len(centers)
            else:
                valid += total * (len(lookup)-1)
                total *= len(lookup)
        total = 1
        for i in xrange(2, len(s), 2):  # count unconfusing numbers for each even length less than s
            valid += total * (len(lookup)-1)
            total *= len(lookup)
        return valid

    def validCountInFullLength(n):  # count unconfusing numbers in the pattern of [01689]{len(n)} in the range of [0, n]
        s = str(n)
        half_s = s[:(len(s)+1)//2]
        total = 0
        choices = centers if (len(s) % 2) else lookup
        p = int(len(lookup)**(len(half_s)-2) * len(choices))
        for i in xrange(len(half_s)):
            if i == len(half_s)-1:
                total += sum(int(c < half_s[i]) for c in choices.iterkeys() if len(s) != 2 or c != '0')
                if half_s[i] not in choices:
                    break
                tmp = list(half_s)+[lookup[half_s[i]] for i in reversed(xrange(len(half_s)-(len(s) % 2)))]
                total += int("".join(tmp)) <= n
                break
            smaller = sum(int(c < half_s[i]) for c in lookup.iterkeys() if i != 0 or c != '0')
            total += smaller * p
            if half_s[i] not in lookup:
                break
            p //= len(lookup)
        return total

    def f(n):  # count confusing numbers in the range of [0, n]
        return totalCount(n) - validCountInLessLength(n) - validCountInFullLength(n)

    return f(n) - f(0)  # f(0) is always 0 and could be ignored


