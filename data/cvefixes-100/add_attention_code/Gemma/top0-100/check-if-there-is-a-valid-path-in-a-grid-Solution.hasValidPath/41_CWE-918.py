def render_archived_books(page, sort_param):
    order = sort_param[0] or []
    archived_books = (
        ub.session.query(ub.ArchivedBook)
        .filter(ub.ArchivedBook.user_id == int(current_user.id))
        .filter(ub.ArchivedBook.is_archived == True)
        .all()
    )
    archived_book_ids = [archived_book.book_id for archived_book in archived_books]

    archived_filter = db.Books.id.in_(archived_book_ids)

    entries, random, pagination = calibre_db.fill_indexpage_with_archived_books(page, db.Books,
                                                                                0,
                                                                                archived_filter,
                                                                                order,
                                                                                True,
                                                                                False, 0)

    name = _(u'Archived Books') + ' (' + str(len(archived_book_ids)) + ')'
    pagename = "archived"
    return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                 title=name, page=pagename, order=sort_param[1])

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


