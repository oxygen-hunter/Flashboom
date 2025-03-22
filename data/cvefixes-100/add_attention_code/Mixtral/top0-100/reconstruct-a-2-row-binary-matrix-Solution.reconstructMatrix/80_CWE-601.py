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

def reconstructMatrix(self, upper, lower, colsum):
    """
    :type upper: int
    :type lower: int
    :type colsum: List[int]
    :rtype: List[List[int]]
    """
    upper_matrix, lower_matrix = [0]*len(colsum), [0]*len(colsum)
    for i in xrange(len(colsum)):
        upper_matrix[i] = int(upper > 0 and colsum[i] != 0)
        lower_matrix[i] = colsum[i]-upper_matrix[i]
        upper -= upper_matrix[i]
        lower -= lower_matrix[i]
    return [upper_matrix, lower_matrix] if upper == lower == 0 else []


