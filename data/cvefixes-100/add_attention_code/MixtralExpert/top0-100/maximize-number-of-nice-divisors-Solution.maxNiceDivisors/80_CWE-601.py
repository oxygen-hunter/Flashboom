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

def maxNiceDivisors(self, primeFactors):
    """
    :type primeFactors: int
    :rtype: int
    """
    # given a1 + a2 + ... + ak <= n, find max of a1 * a2 * ... * ak 
    # => given a1 + a2 + ... + ak = n, find max of a1 * a2 * ... * ak 
    # => ai is either 3 or 2, see proof in "343. integer break"
    MOD = 10**9 + 7
    if primeFactors <= 3:
        return primeFactors
    if primeFactors % 3 == 0:  # 6 => 3*3
        return pow(3, primeFactors//3, MOD)
    if primeFactors % 3 == 1:  # 4 => 2*2 
        return (2*2*pow(3, (primeFactors-4)//3, MOD)) % MOD
    return (2*pow(3, (primeFactors-2)//3, MOD)) % MOD  # 5 => 2*3


