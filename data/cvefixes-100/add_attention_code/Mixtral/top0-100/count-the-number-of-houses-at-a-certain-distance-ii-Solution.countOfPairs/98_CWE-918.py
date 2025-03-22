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

def countOfPairs(self, n, x, y):
    """
    :type n: int
    :type x: int
    :type y: int
    :rtype: List[int]
    """
    x, y = x-1, y-1
    if x > y:
        x, y = y, x
    diff = [0]*n
    for i in xrange(n):
        diff[0] += 1+1                                         # i -> two routes begin
        diff[min(abs(i-x), abs(i-y)+1)] += 1                   # i -> x -> y, fork one route at x to y
        diff[min(abs(i-y), abs(i-x)+1)] += 1                   # i -> y -> x, fork one route at y to x
        diff[min(abs(i-0), abs(i-y)+1+abs(x-0))] -= 1          # i -> 0, one route ends
        diff[min(abs(i-(n-1)), abs(i-x)+1+abs(y-(n-1)))] -= 1  # i -> n-1, one route ends
        diff[max(x-i, 0)+max(i-y, 0)+((y-x)+0)//2] -= 1        # i -> x -> ((y-x)+0)//2 <- x, one route ends
        diff[max(x-i, 0)+max(i-y, 0)+((y-x)+1)//2] -= 1        # i -> y -> ((y-x)+1)//2 <- y, one route ends
    for i in xrange(n-1):
        diff[i+1] += diff[i]
    return diff


