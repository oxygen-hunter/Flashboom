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

def maxPartitionsAfterOperations(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: int
    """
    def popcount(n):
        n = (n & 0x55555555) + ((n >> 1) & 0x55555555)
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333)
        n = (n & 0x0F0F0F0F) + ((n >> 4) & 0x0F0F0F0F)
        n = (n & 0x00FF00FF) + ((n >> 8) & 0x00FF00FF)
        n = (n & 0x0000FFFF) + ((n >> 16) & 0x0000FFFF)
        return n

    left = [0]*(len(s)+1)
    left_mask = [0]*(len(s)+1)
    cnt = mask = 0
    for i in xrange(len(s)):
        mask |= 1<<(ord(s[i])-ord('a'))
        if popcount(mask) > k:
            cnt += 1
            mask = 1<<(ord(s[i])-ord('a'))
        left[i+1] = cnt
        left_mask[i+1] = mask
    right = [0]*(len(s)+1)
    right_mask = [0]*(len(s)+1)
    cnt = mask = 0
    for i in reversed(xrange(len(s))):
        mask |= 1<<(ord(s[i])-ord('a'))
        if popcount(mask) > k:
            cnt += 1
            mask = 1<<(ord(s[i])-ord('a'))
        right[i] = cnt
        right_mask[i] = mask

    result = 0
    for i in xrange(len(s)):
        curr = left[i]+right[i+1]
        mask = left_mask[i]|right_mask[i+1]
        if popcount(left_mask[i]) == popcount(right_mask[i+1]) == k and popcount(mask) != 26:
            curr += 3
        elif popcount(mask)+int(popcount(mask) != 26) > k:  # test case: s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", k = 26
            curr += 2
        else:
            curr += 1
        result = max(result, curr)
    return result


