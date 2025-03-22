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

def canDistribute(self, nums, quantity):
    """
    :type nums: List[int]
    :type quantity: List[int]
    :rtype: bool
    """
    def nth_element(nums, n, compare=lambda a, b: a < b):
        def tri_partition(nums, left, right, target, compare):
            mid = left
            while mid <= right:
                if nums[mid] == target:
                    mid += 1
                elif compare(nums[mid], target):
                    nums[left], nums[mid] = nums[mid], nums[left]
                    left += 1
                    mid += 1
                else:
                    nums[mid], nums[right] = nums[right], nums[mid]
                    right -= 1
            return left, right

        left, right = 0, len(nums)-1
        while left <= right:
            pivot_idx = random.randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx], compare)
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    count = collections.Counter(nums)
    total = (1<<len(quantity))-1
    requirement = [0]*(total+1)
    for mask in xrange(len(requirement)):  # Time: O(2^m)
        base = 1
        for i in xrange(len(quantity)):  # Time: O(m)
            if mask&base:
                requirement[mask] += quantity[i]
            base <<= 1
    dp = [[0]*(total+1) for _ in xrange(2)]
    dp[0][0] = 1
    i = 0
    cnts = count.values()
    if len(quantity) < len(cnts):  # at most use top m cnts
        nth_element(cnts, len(quantity)-1, lambda a, b: a > b)
        cnts = cnts[:len(quantity)]
    for cnt in cnts:  # Time: O(m)
        dp[(i+1)%2] = [0]*(total+1)
        # submask enumeration:
        # => sum(nCr(m, k) * 2^k for k in xrange(m+1)) = (1 + 2)^m = 3^m
        # => Time: O(3^m), see https://cp-algorithms.com/algebra/all-submasks.html
        for mask in reversed(xrange(total+1)):
            dp[(i+1)%2][mask] |= dp[i%2][mask]
            submask = mask
            while submask > 0:
                if requirement[submask] <= cnt and dp[i%2][mask^submask]:
                    dp[(i+1)%2][mask] = 1
                submask = (submask-1)&mask
        i += 1
    return dp[len(cnts)%2][total]


