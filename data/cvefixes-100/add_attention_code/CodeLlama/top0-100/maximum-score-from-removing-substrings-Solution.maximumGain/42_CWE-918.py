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

def maximumGain(self, s, x, y):
    """
    :type s: str
    :type x: int
    :type y: int
    :rtype: int
    """
    def score(s, a, x):
        i = result = 0
        for j in xrange(len(s)):
            s[i] = s[j]
            i += 1
            if i >= 2 and s[i-2:i] == a:
                i -= 2
                result += x
        s[:] = s[:i]
        return result
            
    s, a, b = list(s), list("ab"), list("ba")
    if x < y:
        x, y = y, x
        a, b = b, a
    return score(s, a, x) + score(s, b, y)


