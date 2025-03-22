def render_downloaded_books(page, order, user_id):
    if current_user.role_admin():
        user_id = int(user_id)
    else:
        user_id = current_user.id
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD):
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()

        entries, __, pagination = calibre_db.fill_indexpage(page,
                                                            0,
                                                            db.Books,
                                                            ub.Downloads.user_id == user_id,
                                                            order[0],
                                                            False, 0,
                                                            db.books_series_link,
                                                            db.Books.id == db.books_series_link.c.book,
                                                            db.Series,
                                                            ub.Downloads, db.Books.id == ub.Downloads.book_id)
        for book in entries:
            if not calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                             .filter(db.Books.id == book.id).first():
                ub.delete_download(book.id)
        user = ub.session.query(ub.User).filter(ub.User.id == user_id).first()
        return render_title_template('index.html',
                                     random=random,
                                     entries=entries,
                                     pagination=pagination,
                                     id=user_id,
                                     title=_(u"Downloaded books by %(user)s",user=user.name),
                                     page="download",
                                     order=order[1])
    else:
        abort(404)

def hasValidPath(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: bool
    """
    E, S, W, N = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    directions = [
        [W, E], [N, S],
        [W, S], [S, E],
        [W, N], [N, E]
    ]

    for r, c in directions[grid[0][0]-1]:
        if not (0 <= r < len(grid) and 0 <= c < len(grid[0])):
            continue
        pr, pc = 0, 0
        while r != len(grid)-1 or c != len(grid[0])-1:
            for dx, dy in directions[grid[r][c]-1]:
                nr, nc = r+dx, c+dy
                if (nr == pr and nc == pc) or \
                   not(0 <= nr < len(grid) and 0 <= nc < len(grid[0])) or \
                   (-dx, -dy) not in directions[grid[nr][nc]-1]:
                    continue
                pr, pc, r, c = r, c, nr, nc
                break
            else:
                return False
        return True
    return len(grid) == len(grid[0]) == 1 


