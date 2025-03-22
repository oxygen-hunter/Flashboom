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

def missingElement(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def missing_count(nums, x):
        return (nums[x]-nums[0]+1)-(x-0+1)

    def check(nums, k, x):
        return k > missing_count(nums, x)

    left, right = 0, len(nums)-1
    while left <= right:  # find the largest right s.t. k > missingCount(nums, x)
        mid = left + (right-left)//2
        if not check(nums, k, mid):
            right = mid-1
        else:
            left = mid+1
    assert(check(nums, k, right))
    return nums[right] + (k-missing_count(nums, right))


