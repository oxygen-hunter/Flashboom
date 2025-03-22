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

def closestMeetingNode(self, edges, node1, node2):
    """
    :type edges: List[int]
    :type node1: int
    :type node2: int
    :rtype: int
    """
    def dfs(node):
        lookup = {}
        i = 0
        while node != -1:
            if node in lookup:
                break
            lookup[node] = i
            i += 1
            node = edges[node]
        return lookup
    
    lookup1, lookup2 = dfs(node1), dfs(node2)
    intersect = set(lookup1.iterkeys())&set(lookup2.iterkeys())
    return min(intersect, key=lambda x: (max(lookup1[x], lookup2[x]), x)) if intersect else -1


