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

def summaryRanges(self, nums):
    ranges = []
    if not nums:
        return ranges

    start, end = nums[0], nums[0]
    for i in xrange(1, len(nums) + 1):
        if i < len(nums) and nums[i] == end + 1:
            end = nums[i]
        else:
            interval = str(start)
            if start != end:
                interval += "->" + str(end)
            ranges.append(interval)
            if i < len(nums):
                start = end = nums[i]

    return ranges



