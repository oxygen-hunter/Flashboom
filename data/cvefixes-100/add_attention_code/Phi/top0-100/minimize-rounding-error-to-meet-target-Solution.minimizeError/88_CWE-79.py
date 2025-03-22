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

def minimizeError(self, prices, target):
    """
    :type prices: List[str]
    :type target: int
    :rtype: str
    """
    def kthElement(nums, k, compare=lambda a, b: a < b):
        def PartitionAroundPivot(left, right, pivot_idx, nums, compare):
            new_pivot_idx = left
            nums[pivot_idx], nums[right] = nums[right], nums[pivot_idx]
            for i in xrange(left, right):
                if compare(nums[i], nums[right]):
                    nums[i], nums[new_pivot_idx] = nums[new_pivot_idx], nums[i]
                    new_pivot_idx += 1

            nums[right], nums[new_pivot_idx] = nums[new_pivot_idx], nums[right]
            return new_pivot_idx

        left, right = 0, len(nums) - 1
        while left <= right:
            pivot_idx = random.randint(left, right)
            new_pivot_idx = PartitionAroundPivot(left, right, pivot_idx, nums, compare)
            if new_pivot_idx == k:
                return
            elif new_pivot_idx > k:
                right = new_pivot_idx - 1
            else:  # new_pivot_idx < k.
                left = new_pivot_idx + 1
    
    errors = []
    lower, upper = 0, 0
    for i, p in enumerate(map(float, prices)):
        lower += int(math.floor(p))
        upper += int(math.ceil(p))
        if p != math.floor(p):
            errors.append(p-math.floor(p))
    if not lower <= target <= upper:
        return "-1"

    lower_round_count = upper-target
    kthElement(errors, lower_round_count)
    result = 0.0
    for i in xrange(len(errors)):
        if i < lower_round_count:
            result += errors[i]
        else:
            result += 1.0-errors[i]
    return "{:.3f}".format(result)


