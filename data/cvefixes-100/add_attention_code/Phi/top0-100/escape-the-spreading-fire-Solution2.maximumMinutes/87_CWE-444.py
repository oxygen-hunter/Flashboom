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

def maximumMinutes(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    FIRE, WALL, PERSON = range(1, 4)
    INF = 10**9
    def bfs(grid):
        time = {FIRE:[[INF]*len(grid[0]) for _ in xrange(len(grid))],
                PERSON:[[INF]*len(grid[0]) for _ in xrange(len(grid))]}
        d = 0
        q = [(r, c, FIRE) for r in xrange(len(grid)) for c in xrange(len(grid[0])) if grid[r][c] == FIRE]
        q.append((0, 0, PERSON))
        for r, c, t in q:
            time[t][r][c] = d
        while q:
            new_q = []
            for r, c, t in q:
                for dr, dc in DIRECTIONS:
                    nr, nc = r+dr, c+dc
                    if not (0 <= nr < len(grid) and 0 <= nc < len(grid[0]) and
                            grid[nr][nc] != WALL and time[t][nr][nc] == INF and
                            (t == FIRE or
                             d+1 < time[FIRE][nr][nc] or (d+1 == time[FIRE][nr][nc] and (nr, nc) == (len(grid)-1, len(grid[0])-1)))):
                        continue
                    time[t][nr][nc] = d+1
                    new_q.append((nr, nc, t))
            q = new_q
            d += 1
        return time

    time = bfs(grid)
    if time[PERSON][-1][-1] == INF:
        return -1
    if time[FIRE][-1][-1] == INF:
        return INF
    diff = time[FIRE][-1][-1]-time[PERSON][-1][-1]
    return diff if diff+2 in (time[FIRE][-1][-2]-time[PERSON][-1][-2], time[FIRE][-2][-1]-time[PERSON][-2][-1]) else diff-1


