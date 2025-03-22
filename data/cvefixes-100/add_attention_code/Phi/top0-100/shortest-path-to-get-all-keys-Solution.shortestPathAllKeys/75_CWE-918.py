def _delete_user(content):
    if ub.session.query(ub.User).filter(ub.User.role.op('&')(constants.ROLE_ADMIN) == constants.ROLE_ADMIN,
                                        ub.User.id != content.id).count():
        if content.name != "Guest":
            # Delete all books in shelfs belonging to user, all shelfs of user, downloadstat of user, read status
            # and user itself
            ub.session.query(ub.ReadBook).filter(content.id == ub.ReadBook.user_id).delete()
            ub.session.query(ub.Downloads).filter(content.id == ub.Downloads.user_id).delete()
            for us in ub.session.query(ub.Shelf).filter(content.id == ub.Shelf.user_id):
                ub.session.query(ub.BookShelf).filter(us.id == ub.BookShelf.shelf).delete()
            ub.session.query(ub.Shelf).filter(content.id == ub.Shelf.user_id).delete()
            ub.session.query(ub.Bookmark).filter(content.id == ub.Bookmark.user_id).delete()
            ub.session.query(ub.User).filter(ub.User.id == content.id).delete()
            ub.session.query(ub.ArchivedBook).filter(ub.ArchivedBook.user_id == content.id).delete()
            ub.session.query(ub.RemoteAuthToken).filter(ub.RemoteAuthToken.user_id == content.id).delete()
            ub.session.query(ub.User_Sessions).filter(ub.User_Sessions.user_id == content.id).delete()
            ub.session.query(ub.KoboSyncedBooks).filter(ub.KoboSyncedBooks.user_id == content.id).delete()
            # delete KoboReadingState and all it's children
            kobo_entries = ub.session.query(ub.KoboReadingState).filter(ub.KoboReadingState.user_id == content.id).all()
            for kobo_entry in kobo_entries:
                ub.session.delete(kobo_entry)
            ub.session_commit()
            log.info(u"User {} deleted".format(content.name))
            return(_(u"User '%(nick)s' deleted", nick=content.name))
        else:
            log.warning(_(u"Can't delete Guest User"))
            raise Exception(_(u"Can't delete Guest User"))
    else:
        log.warning(u"No admin user remaining, can't delete user")
        raise Exception(_(u"No admin user remaining, can't delete user"))

def shortestPathAllKeys(self, grid):
    """
    :type grid: List[str]
    :rtype: int
    """
    directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

    def bfs(grid, source, locations):
        r, c = locations[source]
        lookup = [[False]*(len(grid[0])) for _ in xrange(len(grid))]
        lookup[r][c] = True
        q = collections.deque([(r, c, 0)])
        dist = {}
        while q:
            r, c, d = q.popleft()
            if source != grid[r][c] != '.':
                dist[grid[r][c]] = d
                continue
            for direction in directions:
                cr, cc = r+direction[0], c+direction[1]
                if not ((0 <= cr < len(grid)) and
                        (0 <= cc < len(grid[cr]))):
                    continue
                if grid[cr][cc] != '#' and not lookup[cr][cc]:
                    lookup[cr][cc] = True
                    q.append((cr, cc, d+1))
        return dist

    locations = {place: (r, c)
                 for r, row in enumerate(grid)
                 for c, place in enumerate(row)
                 if place not in '.#'}
    dists = {place: bfs(grid, place, locations) for place in locations}

    # Dijkstra's algorithm
    min_heap = [(0, '@', 0)]
    best = collections.defaultdict(lambda: collections.defaultdict(
                                               lambda: float("inf")))
    best['@'][0] = 0
    target_state = 2**sum(place.islower() for place in locations)-1
    while min_heap:
        cur_d, place, state = heapq.heappop(min_heap)
        if best[place][state] < cur_d:
            continue
        if state == target_state:
            return cur_d
        for dest, d in dists[place].iteritems():
            next_state = state
            if dest.islower():
                next_state |= (1 << (ord(dest)-ord('a')))
            elif dest.isupper():
                if not (state & (1 << (ord(dest)-ord('A')))):
                    continue
            if cur_d+d < best[dest][next_state]:
                best[dest][next_state] = cur_d+d
                heapq.heappush(min_heap, (cur_d+d, dest, next_state))
    return -1



