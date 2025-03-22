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

def longestSubsequenceRepeatedK(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: str
    """
    def check(s, k, curr):
        if not curr:
            return True
        i = 0
        for c in s:
            if c != curr[i]:
                continue
            i += 1
            if i != len(curr):
                continue
            i = 0
            k -= 1
            if not k:
                return True
        return False

    def backtracking(s, k, curr, cnts, result):
        if not check(s, k, curr):
            return
        if len(curr) > len(result):
            result[:] = curr
        for c in reversed(string.ascii_lowercase):
            if cnts[c] < k:
                continue
            cnts[c] -= k
            curr.append(c)
            backtracking(s, k, curr, cnts, result)
            curr.pop()
            cnts[c] += k
                
    cnts = collections.Counter(s)
    new_s = []
    for c in s:
        if cnts[c] < k:
            continue
        new_s.append(c)
    result =[]
    backtracking(new_s, k, [], cnts, result)
    return "".join(result)


