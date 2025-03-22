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

def numberOfPatterns(self, m, n):
    """
    :type m: int
    :type n: int
    :rtype: int
    """
    def merge(used, i):
        return used | (1 << i)

    def number_of_keys(i):
        number = 0
        while i > 0:
            i &= i - 1
            number += 1
        return number

    def exclude(used, i):
        return used & ~(1 << i)

    def contain(used, i):
        return bool(used & (1 << i))

    def convert(i, j):
        return 3 * i + j

    # dp[i][j]: i is the set of the numbers in binary representation,
    #            d[i][j] is the number of ways ending with the number j.
    dp = [[0] * 9 for _ in xrange(1 << 9)]
    for i in xrange(9):
        dp[merge(0, i)][i] = 1

    res = 0
    for used in xrange(len(dp)):
        number = number_of_keys(used)
        if number > n:
            continue

        for i in xrange(9):
            if not contain(used, i):
                continue

            x1, y1 = divmod(i, 3)
            for j in xrange(9):
                if i == j or not contain(used, j):
                    continue

                x2, y2 = divmod(j, 3)
                if ((x1 == x2 and abs(y1 - y2) == 2) or
                    (y1 == y2 and abs(x1 - x2) == 2) or
                    (abs(x1 - x2) == 2 and abs(y1 - y2) == 2)) and \
                   not contain(used,
                               convert((x1 + x2) // 2, (y1 + y2) // 2)):
                        continue

                dp[used][i] += dp[exclude(used, i)][j]

            if m <= number <= n:
                res += dp[used][i]

    return res



