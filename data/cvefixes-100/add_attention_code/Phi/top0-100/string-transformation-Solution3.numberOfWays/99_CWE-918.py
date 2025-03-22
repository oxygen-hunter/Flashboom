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

def numberOfWays(self, s, t, k):
    """
    :type s: str
    :type t: str
    :type k: int
    :rtype: int
    """
    MOD = 10**9+7
    def matrix_mult(A, B):
        ZB = zip(*B)
        return [[sum(a*b % MOD for a, b in itertools.izip(row, col)) % MOD for col in ZB] for row in A]
 
    def matrix_expo(A, K):
        result = [[int(i == j) for j in xrange(len(A))] for i in xrange(len(A))]
        while K:
            if K % 2:
                result = matrix_mult(result, A)
            A = matrix_mult(A, A)
            K /= 2
        return result

    # Template: https://cp-algorithms.com/string/z-function.html
    def z_function(s):  # Time: O(n), Space: O(n)
        z = [0]*len(s)
        l, r = 0, 0
        for i in xrange(1, len(z)):
            if i <= r:
                z[i] = min(r-i+1, z[i-l])
            while i+z[i] < len(z) and s[z[i]] == s[i+z[i]]:
                z[i] += 1
            if i+z[i]-1 > r:
                l, r = i, i+z[i]-1
        return z

    n = len(s)
    T = [[0, 1],
         [n-1, (n-1)-1]]
    dp = [1, 0]
    dp = matrix_mult([dp], matrix_expo(T, k))[0]  # [dp[0], dp[1]] * T^k
    z = z_function(t+s+s[:-1])
    return reduce(lambda a, b: (a+b)%MOD, (dp[int(i != 0)] for i in xrange(n) if z[i+len(t)] >= len(t)), 0)


