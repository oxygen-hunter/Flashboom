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

def collectTheCoins(self, coins, edges):
    """
    :type coins: List[int]
    :type edges: List[List[int]]
    :rtype: int
    """
    DISTANCE = 2

    adj = [set() for _ in xrange(len(coins))]
    for u, v in edges:
        adj[u].add(v)
        adj[v].add(u)
    n = len(coins)
    q = []
    for u in xrange(len(coins)):
        while len(adj[u]) == 1 and not coins[u]:
            v = adj[u].pop()
            adj[v].remove(u)
            n -= 1
            u = v
    q = [u for u in xrange(len(coins)) if len(adj[u]) == 1]
    for _ in xrange(DISTANCE):
        new_q = []
        for u in q:
            if not adj[u]:
                assert(n == 1)
                break
            v = adj[u].pop()
            adj[v].remove(u)
            n -= 1
            if len(adj[v]) == 1:
                new_q.append(v)
        q = new_q
    return (n-1)*2


