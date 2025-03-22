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

def medianSlidingWindow(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: List[float]
    """
    def lazy_delete(heap, to_remove, sign):
        while heap and sign*heap[0] in to_remove:
            to_remove[sign*heap[0]] -= 1
            if not to_remove[sign*heap[0]]:
                del to_remove[sign*heap[0]]
            heapq.heappop(heap)

    min_heap, max_heap = [], []
    for i in xrange(k):
        if i%2 == 0:
            heapq.heappush(min_heap, -heapq.heappushpop(max_heap, -nums[i]))
        else:
            heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
    result = [float(min_heap[0])] if k%2 else [(min_heap[0]-max_heap[0])/2.0]
    to_remove = collections.defaultdict(int)
    for i in xrange(k, len(nums)):
        heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
        if nums[i-k] > -max_heap[0]:
            heapq.heappush(min_heap, -heapq.heappop(max_heap))
        to_remove[nums[i-k]] += 1
        lazy_delete(max_heap, to_remove, -1)
        lazy_delete(min_heap, to_remove, 1)
        result.append(float(min_heap[0]) if k%2 else (min_heap[0]-max_heap[0])/2.0)
    return result


