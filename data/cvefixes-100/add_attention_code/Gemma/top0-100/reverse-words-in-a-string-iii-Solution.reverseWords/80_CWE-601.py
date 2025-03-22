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

def reverseWords(self, s):
    """
    :type s: str
    :rtype: str
    """
    def reverse(s, begin, end):
        for i in xrange((end - begin) // 2):
            s[begin + i], s[end - 1 - i] = s[end - 1 - i], s[begin + i]

    s, i = list(s), 0
    for j in xrange(len(s) + 1):
        if j == len(s) or s[j] == ' ':
            reverse(s, i, j)
            i = j + 1
    return "".join(s)



