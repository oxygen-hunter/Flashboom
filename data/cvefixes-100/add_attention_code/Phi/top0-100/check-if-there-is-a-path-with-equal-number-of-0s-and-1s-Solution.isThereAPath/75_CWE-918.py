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

def isThereAPath(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: bool
    """
    if (len(grid)+len(grid[0])-1)%2:
        return False
    dp_left = [[float("inf")]*(len(grid[0])+1) for _ in xrange(2)]
    dp_left[0][1] = dp_left[1][0] = 0
    dp_right = [[float("-inf")]*(len(grid[0])+1) for _ in xrange(2)]
    dp_right[0][1] = dp_right[1][0] = 0
    for i in xrange(len(grid)):
        for j in xrange(len(grid[0])):
            dp_left[(i+1)%2][j+1] = min(dp_left[i%2][j+1], dp_left[(i+1)%2][j])+grid[i][j]
            dp_right[(i+1)%2][j+1] = max(dp_right[i%2][j+1], dp_right[(i+1)%2][j])+grid[i][j]
    return dp_left[len(grid)%2][-1] <= (len(grid)+len(grid[0])-1)//2 <= dp_right[len(grid)%2][-1]


