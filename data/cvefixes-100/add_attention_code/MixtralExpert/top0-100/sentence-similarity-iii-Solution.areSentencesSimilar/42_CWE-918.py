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

def areSentencesSimilar(self, sentence1, sentence2):
    """
    :type sentence1: str
    :type sentence2: str
    :rtype: bool
    """
    if len(sentence1) > len(sentence2):
        sentence1, sentence2 = sentence2, sentence1
    count = 0
    for idx in (lambda x:x, lambda x:-1-x):
        for i in xrange(len(sentence1)+1):
            c1 = sentence1[idx(i)] if i != len(sentence1) else ' '
            c2 = sentence2[idx(i)] if i != len(sentence2) else ' '
            if c1 != c2:
                break
            if c1 == ' ':
                count += 1
    return count >= sentence1.count(' ')+1


