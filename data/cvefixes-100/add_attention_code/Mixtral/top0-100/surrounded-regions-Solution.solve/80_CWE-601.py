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

def solve(self, board):
    """
    :type board: List[List[str]]
    :rtype: void Do not return anything, modify board in-place instead.
    """
    if not board:
        return

    q = collections.deque()

    for i in xrange(len(board)):
        if board[i][0] == 'O':
            board[i][0] = 'V'
            q.append((i, 0))
        if board[i][len(board[0])-1] == 'O':
            board[i][len(board[0])-1] = 'V'
            q.append((i, len(board[0])-1))

    for j in xrange(1, len(board[0])-1):
        if board[0][j] == 'O':
            board[0][j] = 'V'
            q.append((0, j))
        if board[len(board)-1][j] == 'O':
            board[len(board)-1][j] = 'V'
            q.append((len(board)-1, j))

    while q:
        i, j = q.popleft()
        for x, y in [(i+1, j), (i-1, j), (i, j+1), (i, j-1)]:
            if 0 <= x < len(board) and 0 <= y < len(board[0]) and \
               board[x][y] == 'O':
                board[x][y] = 'V'
                q.append((x, y))

    for i in xrange(len(board)):
        for j in xrange(len(board[0])):
            if board[i][j] != 'V':
                board[i][j] = 'X'
            else:
                board[i][j] = 'O'


