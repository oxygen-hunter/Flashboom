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

def executeInstructions(self, n, startPos, s):
    """
    :type n: int
    :type startPos: List[int]
    :type s: str
    :rtype: List[int]
    """
    directions = {'U':(-1, 0), 'R':(0, 1), 'D':(1, 0), 'L':(0, -1)}
    (x0, y0), (x, y) = startPos, (0, 0)
    result = range(len(s), 0, -1)
    lookup_x = collections.defaultdict(list)
    lookup_y = collections.defaultdict(list)
    lookup_x[x0-x].append(0)
    lookup_y[y0-y].append(0)
    for i, d in enumerate(s):
        dx, dy = directions[d]
        x, y = x+dx, y+dy
        for k in n-x, -x-1:
            if k not in lookup_x:
                continue
            for j in lookup_x[k]:
                result[j] = min(result[j], i-j)
            lookup_x[k] = []
        for k in n-y, -y-1:
            if k not in lookup_y:
                continue
            for j in lookup_y[k]:
                result[j] = min(result[j], i-j)
            lookup_y[k] = []
        lookup_x[x0-x].append(i+1)
        lookup_y[y0-y].append(i+1)
    return result


