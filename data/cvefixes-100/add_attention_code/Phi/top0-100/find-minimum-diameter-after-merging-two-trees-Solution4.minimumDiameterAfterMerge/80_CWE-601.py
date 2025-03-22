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

def minimumDiameterAfterMerge(self, edges1, edges2):
    """
    :type edges1: List[List[int]]
    :type edges2: List[List[int]]
    :rtype: int
    """
    def ceil_divide(a, b):
        return (a+b-1)//2

    def tree_diameter(edges):
        def bfs(root):
            d = new_root = -1
            lookup = [False]*len(adj)
            lookup[root] = True
            q = [root]
            while q:
                d, new_root = d+1, q[0]
                new_q = []
                for u in q:
                    for v in adj[u]:
                        if lookup[v]:
                            continue
                        lookup[v] = True
                        new_q.append(v)
                q = new_q
            return d, new_root
        
        adj = [[] for _ in range(len(edges)+1)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        _, root = bfs(0)
        d, _ = bfs(root)
        return d
    
    d1 = tree_diameter(edges1)
    d2 = tree_diameter(edges2)
    return max(ceil_divide(d1, 2)+1+ceil_divide(d2, 2), d1, d2)


