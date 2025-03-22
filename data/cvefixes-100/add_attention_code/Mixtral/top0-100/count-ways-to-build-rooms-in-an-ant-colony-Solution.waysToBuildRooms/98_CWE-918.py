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

def waysToBuildRooms(self, prevRoom):
    """
    :type prevRoom: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    fact = [1, 1]
    inv = [0, 1]
    inv_fact = [1, 1]
    def nCr(n, k):
        while len(inv) <= n:  # lazy initialization
            fact.append(fact[-1]*len(inv) % MOD)
            inv.append(inv[MOD%len(inv)]*(MOD-MOD//len(inv)) % MOD)  # https://cp-algorithms.com/algebra/module-inverse.html
            inv_fact.append(inv_fact[-1]*inv[-1] % MOD)
        return (fact[n]*inv_fact[n-k] % MOD) * inv_fact[k] % MOD

    def dfs(adj, curr):
        total_ways, total_cnt = 1, 0
        for child in adj[curr]:
            ways, cnt = dfs(adj, child)
            total_cnt += cnt
            total_ways = (((total_ways*ways) % MOD)*nCr(total_cnt, cnt)) % MOD
        return total_ways, total_cnt+1

    adj = [[] for _ in xrange(len(prevRoom))]
    for i in xrange(1, len(prevRoom)):
        adj[prevRoom[i]].append(i)
    return dfs(adj, 0)[0]


