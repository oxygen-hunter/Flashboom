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

def longestDupSubstring(self, S):
    """
    :type S: str
    :rtype: str
    """
    M = 10**9+7
    D = 26

    def check(S, L):
        p = pow(D, L, M)
        curr = reduce(lambda x, y: (D*x+ord(y)-ord('a')) % M, S[:L], 0)
        lookup = collections.defaultdict(list)
        lookup[curr].append(L-1)
        for i in xrange(L, len(S)):
            curr = ((D*curr) % M + ord(S[i])-ord('a') -
                    ((ord(S[i-L])-ord('a'))*p) % M) % M
            if curr in lookup:
                for j in lookup[curr]:  # check if string is the same when hash is the same
                    if S[j-L+1:j+1] == S[i-L+1:i+1]:
                        return i-L+1
            lookup[curr].append(i)
        return 0

    left, right = 1, len(S)-1
    while left <= right:
        mid = left + (right-left)//2
        if not check(S, mid):
            right = mid-1
        else:
            left = mid+1
    result = check(S, right)
    return S[result:result + right]


