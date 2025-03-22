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

def sumOddLengthSubarrays(self, arr):
    """
    :type arr: List[int]
    :rtype: int
    """
    def ceil_divide(a, b):
        return (a+(b-1))//b
 
    # begin\pos |0   i       (n-1)
    # ----------------------------
    # 0          --101....      ↑
    # 1           -010....    i-0+1
    # i            101....      ↓
    #              ← (n-1-i+1) →
    #
    # for each number x with its position i, we want to know how many odd length subarrays is with x,
    # as the graph depicted above,
    # (begin, pos) pair represents a subarray arr[begin:pos+1] containing x, marked 1 if odd length else 0,
    # so the total number of 0 and 1 are exactly the total number of subarrays with x, which is (i-0+1)*((len(arr)-1)-i+1),
    # because the number of 1 is always equal to or one more than the number of 0, (always begins with 1010... and alternatively flips)
    # so there are ceil((i-0+1)*((len(arr)-1)-i+1)/2) odd length subarrays with x
    # 
    return sum(x * ceil_divide((i-0+1)*((len(arr)-1)-i+1), 2) for i, x in enumerate(arr))


