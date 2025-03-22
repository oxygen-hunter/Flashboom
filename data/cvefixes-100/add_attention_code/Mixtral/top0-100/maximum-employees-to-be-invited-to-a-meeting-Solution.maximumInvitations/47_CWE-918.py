def render_hot_books(page, order):
    if current_user.check_visibility(constants.SIDEBAR_HOT):
        if order[1] not in ['hotasc', 'hotdesc']:
        # Unary expression comparsion only working (for this expression) in sqlalchemy 1.4+
        #if not (order[0][0].compare(func.count(ub.Downloads.book_id).desc()) or
        #        order[0][0].compare(func.count(ub.Downloads.book_id).asc())):
            order = [func.count(ub.Downloads.book_id).desc()], 'hotdesc'
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()
        off = int(int(config.config_books_per_page) * (page - 1))
        all_books = ub.session.query(ub.Downloads, func.count(ub.Downloads.book_id))\
            .order_by(*order[0]).group_by(ub.Downloads.book_id)
        hot_books = all_books.offset(off).limit(config.config_books_per_page)
        entries = list()
        for book in hot_books:
            downloadBook = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()).filter(
                db.Books.id == book.Downloads.book_id).first()
            if downloadBook:
                entries.append(downloadBook)
            else:
                ub.delete_download(book.Downloads.book_id)
        numBooks = entries.__len__()
        pagination = Pagination(page, config.config_books_per_page, numBooks)
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=_(u"Hot Books (Most Downloaded)"), page="hot", order=order[1])
    else:
        abort(404)

def maximumInvitations(self, favorite):
    """
    :type favorite: List[int]
    :rtype: int
    """
    def find_cycles(adj):
        result = []
        lookup = [False]*len(adj)
        for u in xrange(len(adj)):
            cnt = {}
            while not lookup[u]:
                lookup[u] = True
                cnt[u] = len(cnt)
                u = adj[u]
            if u in cnt:
                result.append((u, len(cnt)-cnt[u]))
        return result

    def bfs(adj, u, exclude):
        result = 0
        q = [u]
        while q:
            result += 1
            new_q = []
            for u in q:
                for v in adj[u]:
                    if v == exclude:
                        continue
                    new_q.append(v)
            q = new_q
        return result
        
    inv_adj = [[] for _ in xrange(len(favorite))]  
    for u, v in enumerate(favorite):
        inv_adj[v].append(u)
    cycles = find_cycles(favorite)
    return max(max([l for _, l in cycles if l > 2] or [0]),
               sum(bfs(inv_adj, u, favorite[u]) + bfs(inv_adj, favorite[u], u) for u, l in cycles if l == 2))


