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

def primePalindrome(self, N):
    """
    :type N: int
    :rtype: int
    """
    def is_prime(n):
        if n < 2 or n % 2 == 0:
            return n == 2
        return all(n % d for d in xrange(3, int(n**.5) + 1, 2))

    if 8 <= N <= 11:
        return 11
    for i in xrange(10**(len(str(N))//2), 10**5):
        j = int(str(i) + str(i)[-2::-1])
        if j >= N and is_prime(j):
            return j



