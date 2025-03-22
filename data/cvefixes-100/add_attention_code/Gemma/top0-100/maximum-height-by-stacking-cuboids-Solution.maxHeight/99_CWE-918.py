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

def maxHeight(self, cuboids):
    """
    :type cuboids: List[List[int]]
    :rtype: int
    """
    for cuboid in cuboids:
        cuboid.sort()
    cuboids.append([0, 0, 0])
    cuboids.sort()
    dp = [0]*len(cuboids)
    for i in xrange(1, len(cuboids)):
        for j in xrange(i):
            if all(cuboids[j][k] <= cuboids[i][k] for k in xrange(3)):
                dp[i] = max(dp[i], dp[j]+cuboids[i][2])
    return max(dp)


