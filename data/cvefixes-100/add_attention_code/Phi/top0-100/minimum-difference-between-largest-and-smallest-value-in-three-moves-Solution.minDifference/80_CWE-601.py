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

def minDifference(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def nth_element(nums, left, n, right, compare=lambda a, b: a < b):
        def partition_around_pivot(left, right, pivot_idx, nums, compare):
            new_pivot_idx = left
            nums[pivot_idx], nums[right] = nums[right], nums[pivot_idx]
            for i in xrange(left, right):
                if compare(nums[i], nums[right]):
                    nums[i], nums[new_pivot_idx] = nums[new_pivot_idx], nums[i]
                    new_pivot_idx += 1

            nums[right], nums[new_pivot_idx] = nums[new_pivot_idx], nums[right]
            return new_pivot_idx

        while left <= right:
            pivot_idx = random.randint(left, right)
            new_pivot_idx = partition_around_pivot(left, right, pivot_idx, nums, compare)
            if new_pivot_idx == n:
                return
            elif new_pivot_idx > n:
                right = new_pivot_idx - 1
            else:  # new_pivot_idx < n
                left = new_pivot_idx + 1

    k = 4
    if len(nums) <= k:
        return 0
    nth_element(nums, 0, k, len(nums)-1)
    nums[:k] = sorted(nums[:k])
    nth_element(nums, k, max(k, len(nums)-k), len(nums)-1)
    nums[-k:] = sorted(nums[-k:])
    return min(nums[-k+i]-nums[i] for i in xrange(k))


