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

def largestPalindrome(self, n, k):
    """
    :type n: int
    :type k: int
    :rtype: str
    """
    def inv(x, p):
        return pow(x, p-2, p)

    def f(l):
        p = 7
        result = ['9']*l
        if l:                
            curr = reduce(lambda accu, x: (accu*10+(ord(x)-ord('0')))%p, result, 0)
            # l%2 == 0: (curr+(i-9)*11*pow(10, l//2-1, p))%p = 0
            # l%2 == 1: (curr+(i-9)*pow(10, l//2, p))%p = 0
            i = 9-(curr*inv(11 if l%2 == 0 else 1, p)*inv(pow(10, l//2-int(l%2 == 0), p), p))%p
            if i <= 2:
                i += p
            result[l//2] = result[l//2-int(l%2 == 0)] = str(i)
        return "".join(result)

    if k in (1, 3, 9):
        return '9'*n
    if k in (2, 4, 8):
        k = min(k, 6)
        if n <= k:
            return '8'*n
        l = k//2
        return '8'*l+'9'*(n-k)+'8'*l
    if k == 5:
        if n <= 2:
            return '5'*n
        return '5'+'9'*(n-2)+'5'
    if k == 6:
        if n <= 2:
            return '6'*n
        if n%2:
            l = n//2-1
            return '8'+'9'*l+'8'+'9'*l+'8'
        l = n//2-2
        return '8'+'9'*l+"77"+'9'*l+'8'
    l, r = divmod(n, 12)
    return "999999"*l+f(r)+"999999"*l  # 999999%7 = 0


