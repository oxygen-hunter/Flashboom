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

def createSortedArray(self, instructions):
    """
    :type instructions: List[int]
    :rtype: int
    """
    MOD = 10**9 + 7
    def smallerMergeSort(idxs, start, end, counts):
        if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
            return 0

        mid = start + (end - start) // 2
        smallerMergeSort(idxs, start, mid, counts)
        smallerMergeSort(idxs, mid + 1, end, counts)
        r = start
        tmp = []
        for i in xrange(mid+1, end + 1):
            # Merge the two sorted arrays into tmp.
            while r <= mid and idxs[r][0] < idxs[i][0]:
                tmp.append(idxs[r])
                r += 1
            tmp.append(idxs[i])
            counts[idxs[i][1]] += r - start
        while r <= mid:
            tmp.append(idxs[r])
            r += 1
        # Copy tmp back to idxs
        idxs[start:start+len(tmp)] = tmp
    
    def largerMergeSort(idxs, start, end, counts):
        if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
            return 0

        mid = start + (end - start) // 2
        largerMergeSort(idxs, start, mid, counts)
        largerMergeSort(idxs, mid + 1, end, counts)
        r = start
        tmp = []
        for i in xrange(mid+1, end + 1):
            # Merge the two sorted arrays into tmp.
            while r <= mid and idxs[r][0] <= idxs[i][0]:
                tmp.append(idxs[r])
                r += 1
            if r <= mid:
                tmp.append(idxs[i])
            counts[idxs[i][1]] += mid - r + 1
        while r <= mid:
            tmp.append(idxs[r])
            r += 1
        # Copy tmp back to idxs
        idxs[start:start+len(tmp)] = tmp

    idxs = []
    smaller_counts, larger_counts = [[0] * len(instructions) for _ in xrange(2)]
    for i, inst in enumerate(instructions):
        idxs.append((inst, i))
    smallerMergeSort(idxs[:], 0, len(idxs)-1, smaller_counts)
    largerMergeSort(idxs, 0, len(idxs)-1, larger_counts)
    return sum(min(s, l) for s, l in itertools.izip(smaller_counts, larger_counts)) % MOD


