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

def maxProduct(self, s):
    """
    :type s: str
    :rtype: int
    """
    def palindromic_subsequence_length(s, mask):
        result = 0
        left, right = 0, len(s)-1
        left_bit, right_bit = 1<<left, 1<<right
        while left <= right:
            if mask&left_bit == 0:
                left, left_bit = left+1, left_bit<<1
            elif mask&right_bit == 0:
                right, right_bit = right-1, right_bit>>1
            elif s[left] == s[right]:
                result += 1 if left == right else 2
                left, left_bit = left+1, left_bit<<1
                right, right_bit = right-1, right_bit>>1
            else:
                return 0
        return result
    
    dp = [palindromic_subsequence_length(s, mask) for mask in xrange(1<<len(s))]
    result = 0
    for mask in xrange(len(dp)):
        if dp[mask]*(len(s)-dp[mask]) <= result:  # optimize
            continue
        # submask enumeration:
        # => sum(nCr(n, k) * 2^k for k in xrange(n+1)) = (1 + 2)^n = 3^n
        # => Time: O(3^n), see https://cp-algorithms.com/algebra/all-submasks.html
        submask = inverse_mask = (len(dp)-1)^mask
        while submask:
            result = max(result, dp[mask]*dp[submask])
            submask = (submask-1)&inverse_mask
    return result


