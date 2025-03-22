def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

def shortestBeautifulSubstring(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: str
    """
    def check(r1, r2):
        if r1[1]-r1[0]+1 > r2[1]-r2[0]+1:
            return False
        if r1[1]-r1[0]+1 < r2[1]-r2[0]+1:
            return True
        for i, j in itertools.izip(xrange(r1[0], r1[1]+1), xrange(r2[0], r2[1]+1)):
            if s[i] != s[j]:
                return s[i] < s[j]
        return False

    result = []
    left = curr = 0
    for right in xrange(len(s)):
        curr += s[right] == '1'
        while curr == k+1:
            curr -= s[left] == '1'
            left += 1
        while left < len(s) and s[left] == '0':
            left += 1
        if curr == k:
            if not result or check([left, right], result):
                result = [left, right]
    return s[result[0]:result[1]+1] if result else ""


