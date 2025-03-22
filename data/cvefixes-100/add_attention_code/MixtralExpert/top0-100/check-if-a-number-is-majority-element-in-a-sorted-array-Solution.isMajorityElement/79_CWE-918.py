def _check_login_status(self, request: Request) -> LoginButton:
    # Each time the page is refreshed or loaded, check if the user is logged in and adapt label
    session = getattr(request, "session", None) or getattr(
        request.request, "session", None
    )
    if session is None or "oauth_info" not in session:
        return LoginButton(value=self.value, interactive=True)
    else:
        username = session["oauth_info"]["userinfo"]["preferred_username"]
        logout_text = self.logout_value.format(username)
        return LoginButton(logout_text, interactive=True)

def isMajorityElement(self, nums, target):
    """
    :type nums: List[int]
    :type target: int
    :rtype: bool
    """
    if len(nums) % 2:
        if nums[len(nums)//2] != target:
            return False
    else:
        if not (nums[len(nums)//2-1] == nums[len(nums)//2] == target):
            return False

    left = bisect.bisect_left(nums, target)
    right= bisect.bisect_right(nums, target)
    return (right-left)*2 > len(nums)


