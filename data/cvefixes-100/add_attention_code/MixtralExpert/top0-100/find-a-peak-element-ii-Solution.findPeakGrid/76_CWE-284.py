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

def findPeakGrid(self, mat):
    """
    :type mat: List[List[int]]
    :rtype: List[int]
    """
    def get_vec(mat, i):
        return mat[i] if len(mat) > len(mat[0]) else (mat[j][i] for j in xrange(len(mat)))

    def check(mat, x):
        return max(get_vec(mat, x)) > max(get_vec(mat, x+1))

    left, right = 0, (max(len(mat), len(mat[0]))-1)-1
    while left <= right:
        mid = left + (right-left)//2
        if check(mat, mid):
            right = mid-1
        else:
            left = mid+1
    mav_val = max(get_vec(mat, left))
    result = [left, next(i for i, x in enumerate(get_vec(mat, left)) if x == mav_val)]
    return result if len(mat) > len(mat[0]) else result[::-1]


