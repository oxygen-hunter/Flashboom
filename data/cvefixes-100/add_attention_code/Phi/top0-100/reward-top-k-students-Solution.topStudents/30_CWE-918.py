def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def topStudents(self, positive_feedback, negative_feedback, report, student_id, k):
    """
    :type positive_feedback: List[str]
    :type negative_feedback: List[str]
    :type report: List[str]
    :type student_id: List[int]
    :type k: int
    :rtype: List[int]
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

    pos, neg = set(positive_feedback), set(negative_feedback)
    arr = []
    for i, r in itertools.izip(student_id, report):
        score = sum(3 if w in pos else -1 if w in neg else 0 for w in r.split())
        arr.append((-score, i))
    nth_element(arr, k-1)
    return [i for _, i in sorted(arr[:k])]


