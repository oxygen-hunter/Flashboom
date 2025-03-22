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

def stoneGameIX(self, stones):
    """
    :type stones: List[int]
    :rtype: bool
    """
    count = collections.Counter(x%3 for x in stones)
    if count[0]%2 == 0:
        # iff both counts are not zero, then alice takes the least one at first, the remains are deterministic for bob to lose:
        # - assumed count[1] is the least one:
        #   1(,1,2)*,2,(,2)* => bob loses
        #            ^
        # - assumed count[2] is the least one:
        #   2(,2,1)*,1,(,1)* => bob loses
        #            ^
        return count[1] and count[2]
    # iff abs(count[1] - count[2]) >= 3, then alice takes the most one at first, the remains are deterministic for bob to lose:
    # - assumed count[1] is the most one
    #   1(,1,2)*,0,1(,2,1)*,1,(,1)* => bob loses
    #                       ^
    #   1(,1,2)*,1,0,1,(,1)* => bob loses
    #                ^
    # - assumed count[2] is the most one
    #   2(,2,1)*,0,2(,1,2)*,2,(,2)* => bob loses
    #                       ^
    #   2(,2,1)*,2,0,2,(,2)* => bob loses
    #                ^
    return abs(count[1]-count[2]) >= 3  


