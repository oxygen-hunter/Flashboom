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

def countRoutes(self, locations, start, finish, fuel):
    """
    :type locations: List[int]
    :type start: int
    :type finish: int
    :type fuel: int
    :rtype: int
    """
    MOD = 10**9+7

    s, f = locations[start], locations[finish]
    locations.sort()
    start, finish = bisect.bisect_left(locations, s), bisect.bisect_left(locations, f)

    left = [[0]*(fuel+1) for _ in xrange(len(locations))]  # left[i][f], last move is toward left to location i by f fuel
    right = [[0]*(fuel+1) for _ in xrange(len(locations))]  # right[i][f], last move is toward right to location i by f fuel
    for f in xrange(1, fuel+1):
        for j in xrange(len(locations)-1):
            d = locations[j+1]-locations[j]
            if f > d:
                # left[j][f] = right[j+1][f-d(j, j+1)] + 2*right[j+2][f-d(j, j+2)] + ... + 2^(k-1)*right[j+k][f-d(j, j+k)]
                # => left[j+1][f] = (ight[j+2][f-d(j+1, j+2)] + 2*right[j+3][f-d(j+1, j+3)] + ... + 2^(k-2)*right[j+1+k-1][f-d(j+1, j+1+k-1)]
                # => left[j+1][f-d(j, j+1)] = right[j+2][f-d(j, j+2)] + 2*right[j+3][f-d(j, j+3)] + ... + 2^(k-2)*right[j+k][f-d(j, j+k)]
                # => left[j][f] = right[j+1][f-d(j, j+1)] + 2*left[j+1][f-d(j, j+1)]
                left[j][f] = (right[j+1][f-d] + 2*left[j+1][f-d] % MOD) % MOD
            elif f == d:
                left[j][f] = int(j+1 == start)
        for j in xrange(1, len(locations)):
            d = locations[j]-locations[j-1]
            if f > d:
                # right[j][f] = left[j-1][f-d(j, j-1)] + 2*left[j-2][f-d(j, j-2)] + ... + 2^(k-1)*left[j-k][f-d(j, j-k)]
                # => right[j-1][f] = left[j-2][f-d(j-1, j-2)] + 2*left[j-3][f-d(j-1, j-3)] + ... + 2^(k-2)*left[j-1-k+1][f-d(j-1, j-1-k+1)]
                # => right[j-1][f-d(j, j-1)] = left[j-2][f-d(j, j-2)] + 2*left[j-3][f-d(j, j-3)] + ... + 2^(k-2)*left[j-k][f-d(j, j-k)]
                # => right[j][f] = left[j-1][f-d(j, j-1)] + 2*right[j-1][f-d(j, j-1)]
                right[j][f] = (left[j-1][f-d] + 2*right[j-1][f-d] % MOD) % MOD
            elif f == d:
                right[j][f] = int(j-1 == start)
    result = int(start == finish)
    for f in xrange(1, fuel+1):
        result = ((result + left[finish][f]) % MOD + right[finish][f]) % MOD
    return result



