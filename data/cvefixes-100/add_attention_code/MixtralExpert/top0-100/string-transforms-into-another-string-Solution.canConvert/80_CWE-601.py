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

def canConvert(self, str1, str2):
    """
    :type str1: str
    :type str2: str
    :rtype: bool
    """
    if str1 == str2:
        return True
    lookup = {}
    for i, j in itertools.izip(str1, str2):
        if lookup.setdefault(i, j) != j:
            return False
    return len(set(str2)) < 26


