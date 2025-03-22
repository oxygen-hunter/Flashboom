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

def findRotation(self, mat, target):
    """
    :type mat: List[List[int]]
    :type target: List[List[int]]
    :rtype: bool
    """
    checks = [lambda i, j: mat[i][j] == target[i][j],
              lambda i, j: mat[i][j] == target[j][-1-i],
              lambda i, j: mat[i][j] == target[-1-i][-1-j],
              lambda i, j: mat[i][j] == target[-1-j][i]]
    traverse = lambda check: all(check(i, j) for i in xrange(len(mat)) for j in xrange(len(mat[0])))
    return any(traverse(check) for check in checks)


