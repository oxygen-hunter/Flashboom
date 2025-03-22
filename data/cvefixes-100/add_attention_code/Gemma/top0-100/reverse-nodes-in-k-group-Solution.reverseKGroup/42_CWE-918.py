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

def reverseKGroup(self, head, k):
    dummy = ListNode(-1)
    dummy.next = head

    cur, cur_dummy = head, dummy
    length = 0

    while cur:
        next_cur = cur.next
        length = (length + 1) % k

        if length == 0:
            next_dummy = cur_dummy.next
            self.reverse(cur_dummy, cur.next)
            cur_dummy = next_dummy

        cur = next_cur

    return dummy.next



