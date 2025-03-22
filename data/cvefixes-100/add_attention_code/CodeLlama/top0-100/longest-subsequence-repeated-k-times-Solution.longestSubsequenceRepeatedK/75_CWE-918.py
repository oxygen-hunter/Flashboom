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

def longestSubsequenceRepeatedK(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: str
    """
    def check(s, k, curr):
        if not curr:
            return True
        i = 0
        for c in s:
            if c != curr[i]:
                continue
            i += 1
            if i != len(curr):
                continue
            i = 0
            k -= 1
            if not k:
                return True
        return False

    def backtracking(s, k, curr, cnts, result):
        if not check(s, k, curr):
            return
        if len(curr) > len(result):
            result[:] = curr
        for c in reversed(string.ascii_lowercase):
            if cnts[c] < k:
                continue
            cnts[c] -= k
            curr.append(c)
            backtracking(s, k, curr, cnts, result)
            curr.pop()
            cnts[c] += k
                
    cnts = collections.Counter(s)
    new_s = []
    for c in s:
        if cnts[c] < k:
            continue
        new_s.append(c)
    result =[]
    backtracking(new_s, k, [], cnts, result)
    return "".join(result)


