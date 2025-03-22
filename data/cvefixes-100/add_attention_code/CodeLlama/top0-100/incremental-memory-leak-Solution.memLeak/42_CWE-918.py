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

def memLeak(self, memory1, memory2):
    """
    :type memory1: int
    :type memory2: int
    :rtype: List[int]
    """
    def s(a, d, n):
        return (2*a + (n-1)*d)*n//2

    def f(a, d, x):
        r = int((-(2*a-d)+((2*a-d)**2+8*d*x)**0.5)/(2*d))
        if s(a, d, r) > x:  # adjust float accuracy
            r -= 1
        return r

    is_swapped = False
    if memory1 < memory2:
        memory1, memory2 = memory2, memory1
        is_swapped = True
    n = f(1, 1, memory1-memory2)
    memory1 -= s(1, 1, n)
    if memory1 == memory2:
        is_swapped = False
    l = f(n+1, 2, memory1)
    r = f(n+2, 2, memory2)
    memory1 -= s(n+1, 2, l)
    memory2 -= s(n+2, 2, r)
    if is_swapped:
        memory1, memory2 = memory2, memory1
    return [n+l+r+1, memory1, memory2]


