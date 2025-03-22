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

def countStrobogrammaticUntil(self, num,  can_start_with_0):
    if can_start_with_0 and num in self.cache:
        return self.cache[num]

    count = 0
    if len(num) == 1:
        for c in ['0', '1', '8']:
            if num[0] >= c:
                count += 1
        self.cache[num] = count
        return count

    for key, val in self.lookup.iteritems():
        if can_start_with_0 or key != '0':
            if num[0] > key:
                if len(num) == 2:  # num is like "21"
                    count += 1
                else:  # num is like "201"
                    count += self.countStrobogrammaticUntil('9' * (len(num) - 2), True)
            elif num[0] == key:
                if len(num) == 2:  # num is like 12".
                    if num[-1] >= val:
                        count += 1
                else:
                    if num[-1] >= val:  # num is like "102".
                        count += self.countStrobogrammaticUntil(self.getMid(num), True)
                    elif (self.getMid(num) != '0' * (len(num) - 2)):  # num is like "110".
                        count += self.countStrobogrammaticUntil(self.getMid(num), True) - \
                                 self.isStrobogrammatic(self.getMid(num))

    if not can_start_with_0: # Sum up each length.
        for i in xrange(len(num) - 1, 0, -1):
            count += self.countStrobogrammaticByLength(i)
    else:
        self.cache[num] = count

    return count



