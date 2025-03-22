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

def countStrobogrammaticUntil(self, num,  can_start_with_0):
    if can_start_with_0 and num in self.cache:
        return self.cache[num]

    count = 0
    if len(num) == 1:
        for c in ['0', '1', '8']:
            if num[0] >= c:
                count += 1
        self.cache[num] = count
        return count

    for key, val in self.lookup.iteritems():
        if can_start_with_0 or key != '0':
            if num[0] > key:
                if len(num) == 2:  # num is like "21"
                    count += 1
                else:  # num is like "201"
                    count += self.countStrobogrammaticUntil('9' * (len(num) - 2), True)
            elif num[0] == key:
                if len(num) == 2:  # num is like 12".
                    if num[-1] >= val:
                        count += 1
                else:
                    if num[-1] >= val:  # num is like "102".
                        count += self.countStrobogrammaticUntil(self.getMid(num), True)
                    elif (self.getMid(num) != '0' * (len(num) - 2)):  # num is like "110".
                        count += self.countStrobogrammaticUntil(self.getMid(num), True) - \
                                 self.isStrobogrammatic(self.getMid(num))

    if not can_start_with_0: # Sum up each length.
        for i in xrange(len(num) - 1, 0, -1):
            count += self.countStrobogrammaticByLength(i)
    else:
        self.cache[num] = count

    return count



