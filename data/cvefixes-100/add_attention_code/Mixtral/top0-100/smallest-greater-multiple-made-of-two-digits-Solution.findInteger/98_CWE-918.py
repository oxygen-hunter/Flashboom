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

def findInteger(self, k, digit1, digit2):
    """
    :type k: int
    :type digit1: int
    :type digit2: int
    :rtype: int
    """
    MAX_NUM_OF_DIGITS = 10
    INT_MAX = 2**31-1

    if digit1 < digit2:
        digit1, digit2 = digit2, digit1
    total = 2
    for l in xrange(1, MAX_NUM_OF_DIGITS+1):
        for mask in xrange(total):
            curr, bit = 0, total>>1
            while bit:
                curr = curr*10 + (digit1 if mask&bit else digit2)
                bit >>= 1
            if k < curr <= INT_MAX and curr%k == 0:
                return curr
        total <<= 1
    return -1


