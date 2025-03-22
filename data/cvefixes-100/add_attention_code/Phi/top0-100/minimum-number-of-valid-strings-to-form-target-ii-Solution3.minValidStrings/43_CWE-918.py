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

def minValidStrings(self, words, target):
    """
    :type words: List[str]
    :type target: str
    :rtype: int
    """
    def getPrefix(pattern):
        prefix = [-1]*len(pattern)
        j = -1
        for i in xrange(1, len(pattern)):
            while j+1 > 0 and pattern[j+1] != pattern[i]:
                j = prefix[j]
            if pattern[j+1] == pattern[i]:
                j += 1
            prefix[i] = j
        return prefix

    def KMP(text, pattern, callback):
        prefix = getPrefix(pattern)
        j = -1
        for i in xrange(len(text)):
            while j+1 > 0 and pattern[j+1] != text[i]:
                j = prefix[j]
            if pattern[j+1] == text[i]:
                j += 1
            callback(i, j)
            if j+1 == len(pattern):
                j = prefix[j]

    def update(i, j):
        lookup[i] = max(lookup[i], j+1)

    lookup = [0]*len(target)
    for w in words:
        KMP(target, w, update)
    dp = [0]*(len(target)+1)
    for i in xrange(len(target)):
        if not lookup[i]:
            return -1
        dp[i+1] = dp[(i-lookup[i])+1]+1
    return dp[-1]


