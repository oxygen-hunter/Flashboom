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

def deleteString(self, s):
    """
    :type s: str
    :rtype: int
    """
    MOD, P = 10**9+7, (113, 109)
    def hash(i, j):
        return [(prefix[idx][j+1]-prefix[idx][i]*power[idx][j-i+1])%MOD for idx in xrange(len(P))]

    if all(x == s[0] for x in s):
        return len(s)

    power = [[1] for _ in xrange(len(P))]
    prefix = [[0] for _ in xrange(len(P))]
    for x in s:
        for idx, p in enumerate(P):
            power[idx].append((power[idx][-1]*p)%MOD)
            prefix[idx].append((prefix[idx][-1]*p+(ord(x)-ord('a')))%MOD)
    dp = [1]*len(s)  # dp[i]: max operation count of s[i:]
    for i in reversed(xrange(len(s)-1)):
        for j in xrange(1, (len(s)-i)//2+1):
            if hash(i, i+j-1) == hash(i+j, i+2*j-1):
                dp[i] = max(dp[i], dp[i+j]+1)
    return dp[0]


