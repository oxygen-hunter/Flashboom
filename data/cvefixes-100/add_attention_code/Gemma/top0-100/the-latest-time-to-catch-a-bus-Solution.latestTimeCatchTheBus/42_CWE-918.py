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

def latestTimeCatchTheBus(self, buses, passengers, capacity):
    """
    :type buses: List[int]
    :type passengers: List[int]
    :type capacity: int
    :rtype: int
    """
    buses.sort()
    passengers.sort()
    cnt = j = 0
    for i in xrange(len(buses)-1):
        while j < len(passengers) and passengers[j] <= buses[i]:
            cnt += 1
            j += 1
        cnt = max(cnt-capacity, 0)
    j -= max(cnt-capacity, 0)
    cnt = min(cnt, capacity)
    while j < len(passengers) and passengers[j] <= buses[-1] and cnt+1 <= capacity:
        cnt += 1
        j += 1
    return buses[-1] if cnt < capacity and (j-1 < 0 or passengers[j-1] != buses[-1]) else next(passengers[i]-1 for i in reversed(xrange(j)) if i-1 < 0 or passengers[i]-1 != passengers[i-1])


