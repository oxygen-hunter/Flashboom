def _parse_video(self, video):
    title = video['title']
    vimeo_id = self._search_regex(
        r'https?://player\.vimeo\.com/external/(\d+)',
        video['vimeoVideoURL'], 'vimeo id')

    uploader_id = video.get('hostID')

    return {
        '_type': 'url_transparent',
        'id': vimeo_id,
        'title': title,
        'description': video.get('description'),
        'url': smuggle_url(
            'https://player.vimeo.com/video/' + vimeo_id, {
                'http_headers': {
                    'Referer': 'https://storyfire.com/',
                }
            }),
        'thumbnail': video.get('storyImage'),
        'view_count': int_or_none(video.get('views')),
        'like_count': int_or_none(video.get('likesCount')),
        'comment_count': int_or_none(video.get('commentsCount')),
        'duration': int_or_none(video.get('videoDuration')),
        'timestamp': int_or_none(video.get('publishDate')),
        'uploader': video.get('username'),
        'uploader_id': uploader_id,
        'uploader_url': format_field(uploader_id, None, 'https://storyfire.com/user/%s/video'),
        'episode_number': int_or_none(video.get('episodeNumber') or video.get('episode_number')),
    }

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


