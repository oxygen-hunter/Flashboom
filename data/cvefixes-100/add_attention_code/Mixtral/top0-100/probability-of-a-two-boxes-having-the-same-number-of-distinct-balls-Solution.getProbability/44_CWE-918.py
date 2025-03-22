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

def getProbability(self, balls):
    """
    :type balls: List[int]
    :rtype: float
    """
    def nCrs(n):  # Time: O(n), Space: O(1)
        c = 1
        for k in xrange(n+1):
            yield c
            c *= n-(k+1)+1
            c //= k+1
    
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if n-r < r:
            return nCr(n, n-r)
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c
    
    dp = collections.defaultdict(int)
    dp[0, 0] = 1  # dp[i, j] is the number of ways with number difference i and color difference j
    for n in balls:  # O(k) times
        new_dp = collections.defaultdict(int)
        for (ndiff, cdiff), count in dp.iteritems():  # O(k^2 * n) times
            for k, new_count in enumerate(nCrs(n)):  # O(n) times
                new_ndiff = ndiff+(k-(n-k))
                new_cdiff = cdiff-1 if k == 0 else (cdiff+1 if k == n else cdiff)
                new_dp[new_ndiff, new_cdiff] += count*new_count
        dp = new_dp
    total = sum(balls)
    return float(dp[0, 0])/nCr(total, total//2)


