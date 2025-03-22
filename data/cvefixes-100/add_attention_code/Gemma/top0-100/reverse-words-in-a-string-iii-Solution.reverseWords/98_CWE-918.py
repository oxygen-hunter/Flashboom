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

def reverseWords(self, s):
    """
    :type s: str
    :rtype: str
    """
    def reverse(s, begin, end):
        for i in xrange((end - begin) // 2):
            s[begin + i], s[end - 1 - i] = s[end - 1 - i], s[begin + i]

    s, i = list(s), 0
    for j in xrange(len(s) + 1):
        if j == len(s) or s[j] == ' ':
            reverse(s, i, j)
            i = j + 1
    return "".join(s)



