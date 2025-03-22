def render_read_books(page, are_read, as_xml=False, order=None):
    sort_param = order[0] if order else []
    if not config.config_read_column:
        if are_read:
            db_filter = and_(ub.ReadBook.user_id == int(current_user.id),
                             ub.ReadBook.read_status == ub.ReadBook.STATUS_FINISHED)
        else:
            db_filter = coalesce(ub.ReadBook.read_status, 0) != ub.ReadBook.STATUS_FINISHED
        entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                db.Books,
                                                                db_filter,
                                                                sort_param,
                                                                False, 0,
                                                                db.books_series_link,
                                                                db.Books.id == db.books_series_link.c.book,
                                                                db.Series,
                                                                ub.ReadBook, db.Books.id == ub.ReadBook.book_id)
    else:
        try:
            if are_read:
                db_filter = db.cc_classes[config.config_read_column].value == True
            else:
                db_filter = coalesce(db.cc_classes[config.config_read_column].value, False) != True
            entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                    db.Books,
                                                                    db_filter,
                                                                    sort_param,
                                                                    False, 0,
                                                                    db.books_series_link,
                                                                    db.Books.id == db.books_series_link.c.book,
                                                                    db.Series,
                                                                    db.cc_classes[config.config_read_column])
        except (KeyError, AttributeError):
            log.error("Custom Column No.%d is not existing in calibre database", config.config_read_column)
            if not as_xml:
                flash(_("Custom Column No.%(column)d is not existing in calibre database",
                        column=config.config_read_column),
                      category="error")
                return redirect(url_for("web.index"))
            return [] # ToDo: Handle error Case for opds

    if as_xml:
        return entries, pagination
    else:
        if are_read:
            name = _(u'Read Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "read"
        else:
            name = _(u'Unread Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "unread"
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=name, page=pagename, order=order[1])

def createSortedArray(self, instructions):
    """
    :type instructions: List[int]
    :rtype: int
    """
    MOD = 10**9 + 7
    def smallerMergeSort(idxs, start, end, counts):
        if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
            return 0

        mid = start + (end - start) // 2
        smallerMergeSort(idxs, start, mid, counts)
        smallerMergeSort(idxs, mid + 1, end, counts)
        r = start
        tmp = []
        for i in xrange(mid+1, end + 1):
            # Merge the two sorted arrays into tmp.
            while r <= mid and idxs[r][0] < idxs[i][0]:
                tmp.append(idxs[r])
                r += 1
            tmp.append(idxs[i])
            counts[idxs[i][1]] += r - start
        while r <= mid:
            tmp.append(idxs[r])
            r += 1
        # Copy tmp back to idxs
        idxs[start:start+len(tmp)] = tmp
    
    def largerMergeSort(idxs, start, end, counts):
        if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
            return 0

        mid = start + (end - start) // 2
        largerMergeSort(idxs, start, mid, counts)
        largerMergeSort(idxs, mid + 1, end, counts)
        r = start
        tmp = []
        for i in xrange(mid+1, end + 1):
            # Merge the two sorted arrays into tmp.
            while r <= mid and idxs[r][0] <= idxs[i][0]:
                tmp.append(idxs[r])
                r += 1
            if r <= mid:
                tmp.append(idxs[i])
            counts[idxs[i][1]] += mid - r + 1
        while r <= mid:
            tmp.append(idxs[r])
            r += 1
        # Copy tmp back to idxs
        idxs[start:start+len(tmp)] = tmp

    idxs = []
    smaller_counts, larger_counts = [[0] * len(instructions) for _ in xrange(2)]
    for i, inst in enumerate(instructions):
        idxs.append((inst, i))
    smallerMergeSort(idxs[:], 0, len(idxs)-1, smaller_counts)
    largerMergeSort(idxs, 0, len(idxs)-1, larger_counts)
    return sum(min(s, l) for s, l in itertools.izip(smaller_counts, larger_counts)) % MOD


