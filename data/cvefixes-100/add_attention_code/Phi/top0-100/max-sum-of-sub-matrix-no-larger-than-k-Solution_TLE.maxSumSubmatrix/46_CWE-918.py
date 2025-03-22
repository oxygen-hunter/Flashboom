def render_downloaded_books(page, order, user_id):
    if current_user.role_admin():
        user_id = int(user_id)
    else:
        user_id = current_user.id
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD):
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()

        entries, __, pagination = calibre_db.fill_indexpage(page,
                                                            0,
                                                            db.Books,
                                                            ub.Downloads.user_id == user_id,
                                                            order[0],
                                                            False, 0,
                                                            db.books_series_link,
                                                            db.Books.id == db.books_series_link.c.book,
                                                            db.Series,
                                                            ub.Downloads, db.Books.id == ub.Downloads.book_id)
        for book in entries:
            if not calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                             .filter(db.Books.id == book.id).first():
                ub.delete_download(book.id)
        user = ub.session.query(ub.User).filter(ub.User.id == user_id).first()
        return render_title_template('index.html',
                                     random=random,
                                     entries=entries,
                                     pagination=pagination,
                                     id=user_id,
                                     title=_(u"Downloaded books by %(user)s",user=user.name),
                                     page="download",
                                     order=order[1])
    else:
        abort(404)

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



