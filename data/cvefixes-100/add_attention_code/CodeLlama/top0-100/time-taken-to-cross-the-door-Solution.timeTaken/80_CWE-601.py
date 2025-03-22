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

def timeTaken(self, arrival, state):
    """
    :type arrival: List[int]
    :type state: List[int]
    :rtype: List[int]
    """
    def go_until(t):
        while curr[0] <= t and any(q):
            if not q[direction[0]]:
                direction[0] ^= 1
            result[q[direction[0]].popleft()] = curr[0]
            curr[0] += 1

    UNKNOWN, ENTERING, EXITING = range(-1, 1+1)
    result = [0]*len(arrival)
    curr, direction = [float("-inf")], [UNKNOWN]
    q = [collections.deque(), collections.deque()]
    for i, (a, s) in enumerate(itertools.izip(arrival, state)):
        go_until(a-1)
        q[s].append(i)
        if not (a <= curr[0]):
            curr, direction = [a], [EXITING]
    go_until(float("inf"))
    return result


