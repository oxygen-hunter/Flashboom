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

def isMatch(self, s, p):
    p_ptr, s_ptr, last_s_ptr, last_p_ptr = 0, 0, -1, -1
    last_ptr = []
    while s_ptr < len(s):
        if p_ptr < len(p) and (p_ptr == len(p) - 1 or p[p_ptr + 1] != '*') and \
        (s_ptr < len(s) and (p[p_ptr] == s[s_ptr] or p[p_ptr] == '.')):
                s_ptr += 1
                p_ptr += 1
        elif p_ptr < len(p) - 1 and (p_ptr != len(p) - 1 and p[p_ptr + 1] == '*'):
            p_ptr += 2
            last_ptr.append([s_ptr, p_ptr])
        elif  last_ptr:
            [last_s_ptr, last_p_ptr] = last_ptr.pop()
            while last_ptr and p[last_p_ptr - 2] != s[last_s_ptr] and p[last_p_ptr - 2] != '.':
                [last_s_ptr, last_p_ptr] = last_ptr.pop()

            if p[last_p_ptr - 2] == s[last_s_ptr] or p[last_p_ptr - 2] == '.':
                last_s_ptr += 1
                s_ptr = last_s_ptr
                p_ptr = last_p_ptr
                last_ptr.append([s_ptr, p_ptr])
            else:
                return False
        else:
            return False

    while p_ptr < len(p) - 1 and p[p_ptr] == '.' and p[p_ptr + 1] == '*':
        p_ptr += 2

    return p_ptr == len(p)



