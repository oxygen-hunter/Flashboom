def convert_bookformat(book_id):
    # check to see if we have form fields to work with -  if not send user back
    book_format_from = request.form.get('book_format_from', None)
    book_format_to = request.form.get('book_format_to', None)

    if (book_format_from is None) or (book_format_to is None):
        flash(_(u"Source or destination format for conversion missing"), category="error")
        return redirect(url_for('editbook.edit_book', book_id=book_id))

    log.info('converting: book id: %s from: %s to: %s', book_id, book_format_from, book_format_to)
    rtn = helper.convert_book_format(book_id, config.config_calibre_dir, book_format_from.upper(),
                                     book_format_to.upper(), current_user.name)

    if rtn is None:
        flash(_(u"Book successfully queued for converting to %(book_format)s",
                    book_format=book_format_to),
                    category="success")
    else:
        flash(_(u"There was an error converting this book: %(res)s", res=rtn), category="error")
    return redirect(url_for('editbook.edit_book', book_id=book_id))

def maxUpgrades(self, count, upgrade, sell, money):
    """
    :type count: List[int]
    :type upgrade: List[int]
    :type sell: List[int]
    :type money: List[int]
    :rtype: List[int]
    """
    # let x be the number of sold servers
    # (c-x)*u <= m+(x*s)
    # -x <= (m-c*u)//(u+s) <= 0
    # c-x <= c+(m-c*u)//(u+s) <= c
    return [min(c+(m-c*u)//(u+s), c) for c, u, s, m in itertools.izip(count, upgrade, sell, money)]


