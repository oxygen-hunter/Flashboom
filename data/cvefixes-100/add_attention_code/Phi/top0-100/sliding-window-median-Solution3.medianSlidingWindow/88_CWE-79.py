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

def medianSlidingWindow(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: List[float]
    """
    def lazy_delete(heap, to_remove, sign):
        while heap and sign*heap[0] in to_remove:
            to_remove[sign*heap[0]] -= 1
            if not to_remove[sign*heap[0]]:
                del to_remove[sign*heap[0]]
            heapq.heappop(heap)

    min_heap, max_heap = [], []
    for i in xrange(k):
        if i%2 == 0:
            heapq.heappush(min_heap, -heapq.heappushpop(max_heap, -nums[i]))
        else:
            heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
    result = [float(min_heap[0])] if k%2 else [(min_heap[0]-max_heap[0])/2.0]
    to_remove = collections.defaultdict(int)
    for i in xrange(k, len(nums)):
        heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
        if nums[i-k] > -max_heap[0]:
            heapq.heappush(min_heap, -heapq.heappop(max_heap))
        to_remove[nums[i-k]] += 1
        lazy_delete(max_heap, to_remove, -1)
        lazy_delete(min_heap, to_remove, 1)
        result.append(float(min_heap[0]) if k%2 else (min_heap[0]-max_heap[0])/2.0)
    return result


