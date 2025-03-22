def _get_unauth_response(self, request, reason):
    """
    Get an error response (or raise a Problem) for a given request and reason message.

    :type request: Request.
    :param request: HttpRequest
    :type reason: Reason string.
    :param reason: str
    """
    if request.is_ajax():
        return HttpResponseForbidden(json.dumps({"error": force_text(reason)}))
    error_params = urlencode({"error": force_text(reason)})
    login_url = force_str(reverse("shuup_admin:login") + "?" + error_params)
    resp = redirect_to_login(next=request.path, login_url=login_url)
    if is_authenticated(request.user):
        # Instead of redirecting to the login page, let the user know what's wrong with
        # a helpful link.
        raise (
            Problem(_("Can't view this page. %(reason)s") % {"reason": reason}).with_link(
                url=resp.url, title=_("Log in with different credentials...")
            )
        )
    return resp

def maximumStrongPairXor(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    class Trie(object):
        def __init__(self, bit_length):
            self.__nodes = []
            self.__mins = []
            self.__maxs = []
            self.__new_node()
            self.__bit_length = bit_length
        
        def __new_node(self):
            self.__nodes.append([-1]*2)
            self.__mins.append(float("inf"))
            self.__maxs.append(float("-inf"))
            return len(self.__nodes)-1

        def insert(self, num):
            curr = 0
            for i in reversed(xrange(self.__bit_length)):
                x = num>>i
                if self.__nodes[curr][x&1] == -1:
                    self.__nodes[curr][x&1] = self.__new_node()
                curr = self.__nodes[curr][x&1]
                self.__mins[curr] = min(self.__mins[curr], num)
                self.__maxs[curr] = max(self.__maxs[curr], num)
                    
        def query(self, num):
            result = curr = 0
            for i in reversed(xrange(self.__bit_length)):
                result <<= 1
                x = num>>i
                y = (result|1)^x
                assert(x != y) 
                if (self.__nodes[curr][y&1] != -1 and
                    ((x > y and num <= 2*self.__maxs[self.__nodes[curr][y&1]]) or
                     (x < y and self.__mins[self.__nodes[curr][y&1]] <= 2*num))):
                    result |= 1
                    curr = self.__nodes[curr][y&1]
                else:
                    curr = self.__nodes[curr][1^(y&1)]
            return result

    trie = Trie(max(nums).bit_length())
    result = 0
    for num in nums:
        trie.insert(num)
        result = max(result, trie.query(num))
    return result



