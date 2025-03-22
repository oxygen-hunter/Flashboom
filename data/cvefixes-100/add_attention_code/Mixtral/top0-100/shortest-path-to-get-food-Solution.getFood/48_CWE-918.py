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

def getFood(self, grid):
    """
    :type grid: List[List[str]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    q = []
    for r in xrange(len(grid)):
        for c in xrange(len(grid[0])):
            if grid[r][c] == '*':
                q.append((r, c))
                break
    
    result = 0
    while q:
        result += 1
        new_q = []
        for r, c in q:
            for dr, dc in directions:
                nr, nc = r+dr, c+dc
                if not (0 <= nr < len(grid) and
                        0 <= nc < len(grid[0]) and
                        grid[nr][nc] != 'X'):
                    continue
                if grid[nr][nc] == '#':
                    return result
                grid[nr][nc] = 'X'
                new_q.append((nr, nc))
        q = new_q 
    return -1


