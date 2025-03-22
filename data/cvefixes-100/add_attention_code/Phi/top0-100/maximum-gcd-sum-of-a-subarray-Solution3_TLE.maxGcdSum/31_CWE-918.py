def profile():
    languages = calibre_db.speaking_language()
    translations = babel.list_translations() + [LC('en')]
    kobo_support = feature_support['kobo'] and config.config_kobo_sync
    if feature_support['oauth'] and config.config_login_type == 2:
        oauth_status = get_oauth_status()
        local_oauth_check = oauth_check
    else:
        oauth_status = None
        local_oauth_check = {}

    if request.method == "POST":
        change_profile(kobo_support, local_oauth_check, oauth_status, translations, languages)
    return render_title_template("user_edit.html",
                                 translations=translations,
                                 profile=1,
                                 languages=languages,
                                 content=current_user,
                                 kobo_support=kobo_support,
                                 title=_(u"%(name)s's profile", name=current_user.name),
                                 page="me",
                                 registered_oauth=local_oauth_check,
                                 oauth_status=oauth_status)

def maxGcdSum(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def gcd(a, b):
        while b:
            a, b = b, a%b
        return a

    def binary_search_right(left, right, check):
        while left <= right:
            mid = left + (right-left)//2
            if not check(mid):
                right = mid-1
            else:
                left = mid+1
        return right

    # RMQ - Sparse Table
    # Template: https://github.com/kamyu104/GoogleCodeJam-Farewell-Rounds/blob/main/Round%20D/genetic_sequences2.py3
    # Time:  ctor:  O(NlogN) * O(fn)
    #        query: O(fn)
    # Space: O(NlogN)
    class SparseTable(object):
        def __init__(self, arr, fn):
            self.fn = fn
            self.bit_length = [0]
            n = len(arr)
            k = n.bit_length()-1  # log2_floor(n)
            for i in xrange(k+1):
                self.bit_length.extend(i+1 for _ in xrange(min(1<<i, (n+1)-len(self.bit_length))))
            self.st = [[0]*n for _ in xrange(k+1)]
            self.st[0] = arr[:]
            for i in xrange(1, k+1):  # Time: O(NlogN) * O(fn)
                for j in xrange((n-(1<<i))+1):
                    self.st[i][j] = fn(self.st[i-1][j], self.st[i-1][j+(1<<(i-1))])
    
        def query(self, L, R):  # Time: O(fn)
            i = self.bit_length[R-L+1]-1  # log2_floor(R-L+1)
            return self.fn(self.st[i][L], self.st[i][R-(1<<i)+1])
    
    prefix = [0]*(len(nums)+1)
    for i, x in enumerate(nums):
        prefix[i+1] = prefix[i]+x
    result = 0
    rmq = SparseTable(nums, gcd)
    for left, x in enumerate(nums):
        right = left
        while right < len(nums):  # O(logr) times
            g = rmq.query(left, right)
            right = binary_search_right(right, len(nums)-1, lambda x: rmq.query(left, x) >= g)  # Time: O(logn) * O(logr)
            if right-left+1 >= k:
                result = max(result, (prefix[right+1]-prefix[left])*g)
            right += 1
    return result


