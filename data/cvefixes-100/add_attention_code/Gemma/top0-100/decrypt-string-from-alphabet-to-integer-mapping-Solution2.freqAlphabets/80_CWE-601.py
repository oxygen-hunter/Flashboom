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

def freqAlphabets(self, s):
    """
    :type s: str
    :rtype: str
    """
    def alpha(num):
        return chr(ord('a') + int(num)-1)

    i = len(s)-1
    result = []
    while i >= 0:
        if s[i] == '#':
            result.append(alpha(s[i-2:i]))
            i -= 3
        else:
            result.append(alpha(s[i]))
            i -= 1
    return "".join(reversed(result))



