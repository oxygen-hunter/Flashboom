def series_list():
    if current_user.check_visibility(constants.SIDEBAR_SERIES):
        if current_user.get_view_property('series', 'dir') == 'desc':
            order = db.Series.sort.desc()
            order_no = 0
        else:
            order = db.Series.sort.asc()
            order_no = 1
        if current_user.get_view_property('series', 'series_view') == 'list':
            entries = calibre_db.session.query(db.Series, func.count('books_series_link.book').label('count')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(text('books_series_link.series')).order_by(order).all()
            charlist = calibre_db.session.query(func.upper(func.substr(db.Series.sort, 1, 1)).label('char')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(func.upper(func.substr(db.Series.sort, 1, 1))).all()
            return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                         title=_(u"Series"), page="serieslist", data="series", order=order_no)
        else:
            entries = calibre_db.session.query(db.Books, func.count('books_series_link').label('count'),
                                               func.max(db.Books.series_index), db.Books.id) \
                .join(db.books_series_link).join(db.Series).filter(calibre_db.common_filters())\
                .group_by(text('books_series_link.series')).order_by(order).all()
            charlist = calibre_db.session.query(func.upper(func.substr(db.Series.sort, 1, 1)).label('char')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(func.upper(func.substr(db.Series.sort, 1, 1))).all()

            return render_title_template('grid.html', entries=entries, folder='web.books_list', charlist=charlist,
                                         title=_(u"Series"), page="serieslist", data="series", bodyClass="grid-view",
                                         order=order_no)
    else:
        abort(404)

def maxGcdSum(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def gcd(a, b):
        while b:
            a, b = b, a%b
        return a

    def binary_search_right(left, right, check):
        while left <= right:
            mid = left + (right-left)//2
            if not check(mid):
                right = mid-1
            else:
                left = mid+1
        return right

    # RMQ - Sparse Table
    # Template: https://github.com/kamyu104/GoogleCodeJam-Farewell-Rounds/blob/main/Round%20D/genetic_sequences2.py3
    # Time:  ctor:  O(NlogN) * O(fn)
    #        query: O(fn)
    # Space: O(NlogN)
    class SparseTable(object):
        def __init__(self, arr, fn):
            self.fn = fn
            self.bit_length = [0]
            n = len(arr)
            k = n.bit_length()-1  # log2_floor(n)
            for i in xrange(k+1):
                self.bit_length.extend(i+1 for _ in xrange(min(1<<i, (n+1)-len(self.bit_length))))
            self.st = [[0]*n for _ in xrange(k+1)]
            self.st[0] = arr[:]
            for i in xrange(1, k+1):  # Time: O(NlogN) * O(fn)
                for j in xrange((n-(1<<i))+1):
                    self.st[i][j] = fn(self.st[i-1][j], self.st[i-1][j+(1<<(i-1))])
    
        def query(self, L, R):  # Time: O(fn)
            i = self.bit_length[R-L+1]-1  # log2_floor(R-L+1)
            return self.fn(self.st[i][L], self.st[i][R-(1<<i)+1])
    
    prefix = [0]*(len(nums)+1)
    for i, x in enumerate(nums):
        prefix[i+1] = prefix[i]+x
    result = 0
    rmq = SparseTable(nums, gcd)
    for left, x in enumerate(nums):
        right = left
        while right < len(nums):  # O(logr) times
            g = rmq.query(left, right)
            right = binary_search_right(right, len(nums)-1, lambda x: rmq.query(left, x) >= g)  # Time: O(logn) * O(logr)
            if right-left+1 >= k:
                result = max(result, (prefix[right+1]-prefix[left])*g)
            right += 1
    return result


