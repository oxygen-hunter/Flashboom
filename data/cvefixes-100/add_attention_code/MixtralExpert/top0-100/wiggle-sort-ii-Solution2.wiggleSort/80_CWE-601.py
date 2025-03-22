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

def wiggleSort(self, nums):
    """
    :type nums: List[int]
    :rtype: None Do not return anything, modify nums in-place instead.
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
            pivot_idx = randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx], compare)
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    def reversedTriPartitionWithVI(nums, val):
        def idx(i, N):
            return (1 + 2 * (i)) % N

        N = len(nums) / 2 * 2 + 1
        i, j, n = 0, 0, len(nums) - 1
        while j <= n:
            if nums[idx(j, N)] > val:
                nums[idx(i, N)], nums[idx(j, N)] = nums[idx(j, N)], nums[idx(i, N)]
                i += 1
                j += 1
            elif nums[idx(j, N)] < val:
                nums[idx(j, N)], nums[idx(n, N)] = nums[idx(n, N)], nums[idx(j, N)]
                n -= 1
            else:
                j += 1

    mid = (len(nums)-1)//2
    nth_element(nums, mid)
    reversedTriPartitionWithVI(nums, nums[mid])


