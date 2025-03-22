def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

def watchedVideosByFriends(self, watchedVideos, friends, id, level):
    """
    :type watchedVideos: List[List[str]]
    :type friends: List[List[int]]
    :type id: int
    :type level: int
    :rtype: List[str]
    """
    curr_level, lookup = set([id]), set([id])
    for _ in xrange(level):
        curr_level = set(j for i in curr_level for j in friends[i] if j not in lookup)
        lookup |= curr_level
    count = collections.Counter([v for i in curr_level for v in watchedVideos[i]])
    return sorted(count.keys(), key=lambda x: (count[x], x))


