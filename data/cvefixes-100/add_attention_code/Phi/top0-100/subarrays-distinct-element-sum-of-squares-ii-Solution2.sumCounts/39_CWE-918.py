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

def sumCounts(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    # Template:
    # https://github.com/kamyu104/LeetCode-Solutions/blob/master/Python/longest-substring-of-one-repeating-character.py
    class SegmentTree(object):
        def __init__(self, N,
                     build_fn=None,
                     query_fn=lambda x, y: y if x is None else x if y is None else (x+y)%MOD,
                     update_fn=lambda x, y: y if x is None else (x+y)%MOD):
            self.tree = [None]*(1<<((N-1).bit_length()+1))
            self.base = len(self.tree)>>1
            self.lazy = [None]*self.base
            self.query_fn = query_fn
            self.update_fn = update_fn
            if build_fn is not None:
                for i in xrange(self.base, self.base+N):
                    self.tree[i] = build_fn(i-self.base)
                for i in reversed(xrange(1, self.base)):
                    self.tree[i] = query_fn(self.tree[i<<1], self.tree[(i<<1)+1])
            self.count = [1]*len(self.tree)  # added
            for i in reversed(xrange(1, self.base)):  # added
                self.count[i] = self.count[i<<1] + self.count[(i<<1)+1]

        def __apply(self, x, val):
            self.tree[x] = self.update_fn(self.tree[x], val*self.count[x])  # modified
            if x < self.base:
                self.lazy[x] = self.update_fn(self.lazy[x], val)

        def __push(self, x):
            for h in reversed(xrange(1, x.bit_length())):
                y = x>>h
                if self.lazy[y] is not None:
                    self.__apply(y<<1, self.lazy[y])
                    self.__apply((y<<1)+1, self.lazy[y])
                    self.lazy[y] = None

        def update(self, L, R, h):  # Time: O(logN), Space: O(N)
            def pull(x):
                while x > 1:
                    x >>= 1
                    self.tree[x] = self.query_fn(self.tree[x<<1], self.tree[(x<<1)+1])
                    if self.lazy[x] is not None:
                        self.tree[x] = self.update_fn(self.tree[x], self.lazy[x]*self.count[x])  # modified

            L += self.base
            R += self.base
            # self.__push(L)  # enable if range assignment
            # self.__push(R)  # enable if range assignment
            L0, R0 = L, R
            while L <= R:
                if L & 1:  # is right child
                    self.__apply(L, h)
                    L += 1
                if R & 1 == 0:  # is left child
                    self.__apply(R, h)
                    R -= 1
                L >>= 1
                R >>= 1
            pull(L0)
            pull(R0)

        def query(self, L, R):
            if L > R:
                return None
            L += self.base
            R += self.base
            self.__push(L)
            self.__push(R)
            left = right = None
            while L <= R:
                if L & 1:
                    left = self.query_fn(left, self.tree[L])
                    L += 1
                if R & 1 == 0:
                    right = self.query_fn(self.tree[R], right)
                    R -= 1
                L >>= 1
                R >>= 1
            return self.query_fn(left, right)

    result = accu = 0
    sl = {}
    st = SegmentTree(len(nums))
    for i in xrange(len(nums)):
        j = sl[nums[i]] if nums[i] in sl else -1
        # sum(count(k, i)^2 for k in range(i+1)) - sum(count(k, i-1)^2 for k in range(i))
        # = sum(2*count(k, i-1)+1 for k in range(j+1, i+1))
        # = (i-j) + sum(2*count(k, i-1) for k in range(j+1, i+1))
        accu = (accu+((i-j)+2*max(st.query(j+1, i), 0)))%MOD
        result = (result+accu)%MOD
        st.update(j+1, i, 1)  # count(k, i) = count(k, i-1)+(1 if k >= j+1 else 0) for k in range(i+1)
        sl[nums[i]] = i
    return result


