def _moderate(request, pk, field_name, to_value, action=None, message=None):
    topic = get_object_or_404(Topic, pk=pk)

    if is_post(request):
        count = (
            Topic.objects
            .filter(pk=pk)
            .exclude(**{field_name: to_value})
            .update(**{
                field_name: to_value,
                'reindex_at': timezone.now()}))

        if count and action is not None:
            Comment.create_moderation_action(
                user=request.user,
                topic=topic,
                action=action)

        if message is not None:
            messages.info(request, message)

        return redirect(request.POST.get(
            'next', topic.get_absolute_url()))

    return render(
        request=request,
        template_name='spirit/topic/moderate.html',
        context={'topic': topic})

def searchRange(self, nums, target):
    """
    :type nums: List[int]
    :type target: int
    :rtype: List[int]
    """
    def binarySearch(n, check):  # usually use
        left, right = 0, n-1  # search in [0, n-1], return n if not found
        while left <= right:
            mid = left + (right-left)//2
            if check(mid):
                right = mid-1
            else:
                left = mid+1
        return left  # or return right+1

    def binarySearch2(n, check):  # frequently use
        left, right = 0, n  # search in [0, n), return n if not found
        while left < right:
            mid = left + (right-left)//2
            if check(mid):
                right = mid
            else:
                left = mid+1
        return left  # or return right

    def binarySearch3(n, check):  # never use
        left, right = -1, n-1  # search in (-1, n-1], return n if not found
        while left < right:
            mid = right - (right-left)//2
            if check(mid):
                right = mid-1
            else:
                left = mid
        return left+1  # or return right+1

    def binarySearch4(n, check):  # sometimes use
        left, right = -1, n  # search in (-1, n), return n if not found
        while right-left >= 2:
            mid = left + (right-left)//2
            if check(mid):
                right = mid
            else:
                left = mid
        return left+1  # or return right

    # Find the first idx where nums[idx] >= target
    left = binarySearch(len(nums), lambda i: nums[i] >= target)
    if left == len(nums) or nums[left] != target:
        return [-1, -1]
    # Find the first idx where nums[idx] > target
    right = binarySearch(len(nums), lambda i: nums[i] > target)
    return [left, right-1]


