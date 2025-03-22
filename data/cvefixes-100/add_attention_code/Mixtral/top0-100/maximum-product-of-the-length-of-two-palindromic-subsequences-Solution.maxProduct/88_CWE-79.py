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


