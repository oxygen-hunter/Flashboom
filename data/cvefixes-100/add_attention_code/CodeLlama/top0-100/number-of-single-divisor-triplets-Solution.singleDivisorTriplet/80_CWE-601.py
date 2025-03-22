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

def singleDivisorTriplet(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def check(a, b, c):
        return sum((a+b+c)%x == 0 for x in (a, b, c)) == 1

    cnt = collections.Counter(nums)
    return 6*(sum(cnt[a]*cnt[b]*cnt[c] for a, b, c in itertools.combinations(cnt.keys(), 3) if check(a, b, c)) +
              sum(cnt[a]*(cnt[a]-1)//2*cnt[b] for a, b in itertools.permutations(cnt.keys(), 2) if check(a, a, b)))


