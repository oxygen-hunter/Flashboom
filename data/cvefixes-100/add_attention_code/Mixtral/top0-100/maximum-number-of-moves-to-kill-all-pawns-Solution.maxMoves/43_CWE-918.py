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

def maxMoves(self, kx, ky, positions):
    """
    :type kx: int
    :type ky: int
    :type positions: List[List[int]]
    :rtype: int
    """
    N = 50
    DIRECTIONS = ((1, 2), (-1, 2), (1, -2), (-1, -2), (2, 1), (-2, 1), (2, -1), (-2, -1))
    POS_INF = float("inf")
    NEG_INF = float("-inf")
    def popcount(r):
        return bin(r)[2:].count('1')

    def bfs(r, c):
        dist = [[POS_INF]*N for _ in xrange(N)]
        dist[r][c] = 0
        q = [(r, c)]
        while q:
            new_q = []
            for r, c in q:
                for dr, dc in DIRECTIONS:
                    nr, nc = r+dr, c+dc
                    if not (0 <= nr < N and 0 <= nc < N and dist[nr][nc] == POS_INF):
                        continue
                    dist[nr][nc] = dist[r][c]+1
                    new_q.append((nr, nc))
            q = new_q
        return dist

    p = len(positions)
    positions.append([kx, ky])
    dist = [[0]*(p+1) for _ in xrange(p+1)]
    for i, (r, c) in enumerate(positions):
        d = bfs(r, c)
        for j in xrange(i+1, p+1):
            dist[j][i] = dist[i][j] = d[positions[j][0]][positions[j][1]]
    dp = [[POS_INF if popcount(mask)&1 else NEG_INF]*p for mask in xrange(1<<p)]
    dp[-1] = [0]*p
    for mask in reversed(xrange(1, 1<<p)):
        fn = (max, min)[(popcount(mask)&1)^1]
        for i in xrange(p):
            if (mask&(1<<i)) == 0:
                continue
            for j in xrange(p):
                if j == i or (mask&(1<<j)) == 0:
                    continue
                dp[mask^(1<<i)][j] = fn(dp[mask^(1<<i)][j], dp[mask][i]+dist[i][j])
    return max(dp[1<<i][i]+dist[i][p] for i in xrange(p))


