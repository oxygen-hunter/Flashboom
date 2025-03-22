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

def findShortestPath(self, master):
    """
    :type master: GridMaster
    :rtype: int
    """
    directions = {'L': (0, -1), 'R': (0, 1), 'U': (-1, 0), 'D': (1, 0)}
    rollback = {'L': 'R', 'R': 'L', 'U': 'D', 'D': 'U'}

    def dfs(pos, target, master, lookup, adj):
        if target[0] is None and master.isTarget():
            target[0] = pos
        lookup.add(pos)
        for d, (di, dj) in directions.iteritems():
            if not master.canMove(d):
                continue
            nei = (pos[0]+di, pos[1]+dj)
            if nei in adj[pos]:
                continue
            adj[pos][nei] = master.move(d)
            if nei not in lookup:
                dfs(nei, target, master, lookup, adj)
            adj[nei][pos] = master.move(rollback[d])
                    
    def dijkstra(adj, start, target):
        dist = {start:0}
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if dist[u] < curr:
                continue
            for v, w in adj[u].iteritems():
                if v in dist and dist[v] <= curr+w:
                    continue
                dist[v] = curr+w
                heapq.heappush(min_heap, (curr+w, v))
        return dist[target] if target in dist else -1 
    
    start = (0, 0)
    target = [None]
    adj = collections.defaultdict(dict)
    dfs(start, target, master, set(), adj)
    if not target[0]:
        return -1
    return dijkstra(adj, start, target[0])


