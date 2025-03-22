def ratings_list():
    if current_user.check_visibility(constants.SIDEBAR_RATING):
        if current_user.get_view_property('ratings', 'dir') == 'desc':
            order = db.Ratings.rating.desc()
            order_no = 0
        else:
            order = db.Ratings.rating.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Ratings, func.count('books_ratings_link.book').label('count'),
                                   (db.Ratings.rating / 2).label('name')) \
            .join(db.books_ratings_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_ratings_link.rating')).order_by(order).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=list(),
                                     title=_(u"Ratings list"), page="ratingslist", data="ratings", order=order_no)
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



