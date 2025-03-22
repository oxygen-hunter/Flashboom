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

def __create_ac_suffix_and_output_links(self, root):  # Time:  O(n + p^2), Space: O(t + p^2)
    queue = collections.deque()
    for node in root.children.itervalues():
        queue.append(node)
        node.suffix = root

    while queue:
        node = queue.popleft()
        for c, child in node.children.iteritems():
            queue.append(child)
            suffix = node.suffix
            while suffix and c not in suffix.children:
                suffix = suffix.suffix
            child.suffix = suffix.children[c] if suffix else root
            child.outputs += child.suffix.outputs  # Time: O(p^2)
    
    return root



