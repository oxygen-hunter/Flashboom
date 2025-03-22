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

def largestMagicSquare(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    def get_sum(prefix, a, b):
        return prefix[b+1]-prefix[a]

    def check(grid, prefix_row, prefix_col, l, i, j):
        diag, anti_diag = 0, 0
        for d in xrange(l):
            diag += grid[i+d][j+d]
            anti_diag += grid[i+d][j+l-1-d]
        if diag != anti_diag:
            return False
        for ni in xrange(i, i+l):
            if diag != get_sum(prefix_row[ni], j, j+l-1):
                return False
        for nj in xrange(j, j+l):
            if diag != get_sum(prefix_col[nj], i, i+l-1):
                return False  
        return True

    prefix_row = [[0]*(len(grid[0])+1) for _ in xrange(len(grid))]
    prefix_col = [[0]*(len(grid)+1) for _ in xrange(len(grid[0]))]
    for i in xrange(len(grid)):
        for j in xrange(len(grid[0])):
            prefix_row[i][j+1] = prefix_row[i][j] + grid[i][j]
            prefix_col[j][i+1] = prefix_col[j][i] + grid[i][j]
    for l in reversed(xrange(1, min(len(grid), len(grid[0]))+1)):
        for i in xrange(len(grid)-(l-1)):
            for j in xrange(len(grid[0])-(l-1)):
                if check(grid, prefix_row, prefix_col, l, i, j):
                    return l
    return 1


