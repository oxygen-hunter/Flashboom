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

def maxHeight(self, cuboids):
    """
    :type cuboids: List[List[int]]
    :rtype: int
    """
    for cuboid in cuboids:
        cuboid.sort()
    cuboids.append([0, 0, 0])
    cuboids.sort()
    dp = [0]*len(cuboids)
    for i in xrange(1, len(cuboids)):
        for j in xrange(i):
            if all(cuboids[j][k] <= cuboids[i][k] for k in xrange(3)):
                dp[i] = max(dp[i], dp[j]+cuboids[i][2])
    return max(dp)


