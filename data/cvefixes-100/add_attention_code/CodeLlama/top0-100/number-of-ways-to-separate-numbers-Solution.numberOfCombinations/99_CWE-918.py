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

def numberOfCombinations(self, num):
    """
    :type num: str
    :rtype: int
    """
    MOD = 10**9+7
    def find_longest_common_prefix(num):
        lcp = [[0]*(len(num)+1) for _ in xrange(len(num)+1)]  # lcp[i][j]: longest length of the common prefix which starts at num[i], num[j]
        for i in reversed(xrange(len(lcp)-1)):
            for j in reversed(xrange(len(lcp[0])-1)):
                if num[i] == num[j]:
                    lcp[i][j] = lcp[i+1][j+1]+1
        return lcp

    def is_less_or_equal_to_with_same_length(num, lcp, i, j, l):
        return lcp[i][j] >= l or num[i+lcp[i][j]] < num[j+lcp[i][j]]

    lcp = find_longest_common_prefix(num)
    dp = [[0]*len(num) for _ in xrange(len(num))]  # dp[i][l]: the count of numbers ending at num[i], where the length of the last number is l+1
    dp[0][0] = int(num[0] != '0')
    for i in xrange(1, len(num)):
        dp[i][i] = dp[i-1][i-1]
        if num[i] == '0':
            continue
        accu = 0
        for l in xrange(len(num)-i+1):
            ni = i+l-1
            dp[ni][l-1] = accu  # accumulated count where the length of the second to last number ending at num[i-1] is shorter than the length of the last number ending at num[i+l-1]
            if i-l < 0:
                continue
            if num[i-l] != '0' and is_less_or_equal_to_with_same_length(num, lcp, i-l, i, l):
                dp[ni][l-1] = (dp[ni][l-1] + dp[i-1][l-1]) % MOD
            accu = (accu + dp[i-1][l-1]) % MOD
    return reduce(lambda total, x: (total+x)%MOD, dp[-1], 0)


