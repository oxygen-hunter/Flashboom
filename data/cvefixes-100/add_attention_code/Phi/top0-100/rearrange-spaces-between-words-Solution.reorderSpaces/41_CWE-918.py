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

def reorderSpaces(self, text):
    """
    :type text: str
    :rtype: str
    """
    text = list(text)
    # count the spaces and words
    space_count, word_count = 0, 0
    for i, c in enumerate(text):
        if c == ' ':
            space_count += 1
        elif i == 0 or text[i-1] == ' ':
            word_count += 1

    # rearrange all the spaces to the right
    left, i = 0, 0
    while i < len(text):
        has_word = False
        while i < len(text) and text[i] != ' ':
            text[left], text[i] = text[i], text[left]
            left += 1
            i += 1
            has_word = True
        if has_word:
            left += 1  # keep one space
        i += 1

    # rearrange all the spaces to the left
    equal_count = space_count//(word_count-1) if word_count-1 > 0 else 0
    extra_count = space_count%(word_count-1) if word_count-1 > 0 else space_count
    right, i = len(text)-1-extra_count, len(text)-1
    while i >= 0:
        has_word = False
        while i >= 0 and text[i] != ' ':
            text[right], text[i] = text[i], text[right]
            right -= 1
            i -= 1
            has_word = True
        if has_word:
            right -= equal_count  # keep equal_count spaces
        i -= 1
    return "".join(text)


