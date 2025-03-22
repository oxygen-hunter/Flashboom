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

def distributeCandies(self, n, limit):
    """
    :type n: int
    :type limit: int
    :rtype: int
    """
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if not 0 <= r <= n:
            return 0
        if n-r < r:
            r = n-r
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c
    
    def nHr(n, r):
        return nCr(n+(r-1), r-1)

    R = 3
    return sum((-1 if r%2 else 1) * nCr(R, r) * nHr(n-r*(limit+1), R) for r in xrange(R+1))


