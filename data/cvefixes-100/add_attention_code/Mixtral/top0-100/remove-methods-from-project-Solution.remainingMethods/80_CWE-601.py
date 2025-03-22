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

def remainingMethods(self, n, k, invocations):
    """
    :type n: int
    :type k: int
    :type invocations: List[List[int]]
    :rtype: List[int]
    """
    def bfs():
        lookup = [False]*n
        lookup[k] = True
        q = [k]
        while q:
            new_q = []
            for u in q:
                for v in adj[u]:
                    if lookup[v]:
                        continue
                    lookup[v] = True
                    new_q.append(v)
            q = new_q
        return lookup

    adj = [[] for _ in xrange(n)]
    for u, v in invocations:
        adj[u].append(v)
    lookup = bfs()
    return [u for u in xrange(n) if not lookup[u]] if all(lookup[u] == lookup[v] for u, v in invocations) else range(n)


