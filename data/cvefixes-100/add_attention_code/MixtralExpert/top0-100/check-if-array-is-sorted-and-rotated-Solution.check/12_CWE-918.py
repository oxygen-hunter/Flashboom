def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

def check(self, nums):
    """
    :type nums: List[int]
    :rtype: bool
    """
    count = 0
    for i in xrange(len(nums)):
        if nums[i] > nums[(i+1)%len(nums)]:
            count += 1
            if count > 1:
                return False
    return True


