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

def maxSumSubmatrix(self, matrix, k):
    """
    :type matrix: List[List[int]]
    :type k: int
    :rtype: int
    """
    class BST(object):  # not avl, rbtree
        def __init__(self, val):
            self.val = val
            self.left = None
            self.right = None

        def insert(self, val):  # Time: O(h) = O(logn) ~ O(n)
            curr = self
            while curr:
                if curr.val >= val:
                    if curr.left:
                        curr = curr.left
                    else:
                        curr.left = BST(val)
                        return
                else:
                    if curr.right:
                        curr = curr.right
                    else:
                        curr.right = BST(val)
                        return

        def lower_bound(self, val):  # Time: O(h) = O(logn) ~ O(n)
            result, curr = None, self
            while curr:
                if curr.val >= val:
                    result, curr = curr, curr.left
                else:
                    curr = curr.right
            return result


    if not matrix:
        return 0

    m = min(len(matrix), len(matrix[0]))
    n = max(len(matrix), len(matrix[0]))
    result = float("-inf")

    for i in xrange(m):
        sums = [0] * n
        for j in xrange(i, m):
            for l in xrange(n):
                sums[l] += matrix[j][l] if m == len(matrix) else matrix[l][j]

            # Find the max subarray no more than K.
            accu_sum_set = BST(0)
            accu_sum = 0
            for sum in sums:
                accu_sum += sum
                node = accu_sum_set.lower_bound(accu_sum - k)
                if node:
                    result = max(result, accu_sum - node.val)
                accu_sum_set.insert(accu_sum)

    return result



