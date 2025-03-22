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

def shortestBridge(self, A):
    """
    :type A: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    def get_islands(A):
        islands = []
        done = set()
        for r, row in enumerate(A):
            for c, val in enumerate(row):
                if val == 0 or (r, c) in done:
                    continue
                s = [(r, c)]
                lookup = set(s)
                while s:
                    node = s.pop()
                    for d in directions:
                        nei = node[0]+d[0], node[1]+d[1]
                        if not (0 <= nei[0] < len(A) and 0 <= nei[1] < len(A[0])) or \
                           nei in lookup or A[nei[0]][nei[1]] == 0:
                            continue
                        s.append(nei)
                        lookup.add(nei)
                done |= lookup
                islands.append(lookup)
                if len(islands) == 2:
                    break
        return islands

    lookup, target = get_islands(A)
    q = collections.deque([(node, 0) for node in lookup])
    while q:
        node, dis = q.popleft()
        if node in target:
            return dis-1
        for d in directions:
            nei = node[0]+d[0], node[1]+d[1]
            if not (0 <= nei[0] < len(A) and 0 <= nei[1] < len(A[0])) or \
               nei in lookup:
                continue
            q.append((nei, dis+1))
            lookup.add(nei)


