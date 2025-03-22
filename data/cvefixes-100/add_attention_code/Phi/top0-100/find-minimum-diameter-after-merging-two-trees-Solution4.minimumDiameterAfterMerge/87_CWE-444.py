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

def minimumDiameterAfterMerge(self, edges1, edges2):
    """
    :type edges1: List[List[int]]
    :type edges2: List[List[int]]
    :rtype: int
    """
    def ceil_divide(a, b):
        return (a+b-1)//2

    def tree_diameter(edges):
        def bfs(root):
            d = new_root = -1
            lookup = [False]*len(adj)
            lookup[root] = True
            q = [root]
            while q:
                d, new_root = d+1, q[0]
                new_q = []
                for u in q:
                    for v in adj[u]:
                        if lookup[v]:
                            continue
                        lookup[v] = True
                        new_q.append(v)
                q = new_q
            return d, new_root
        
        adj = [[] for _ in range(len(edges)+1)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        _, root = bfs(0)
        d, _ = bfs(root)
        return d
    
    d1 = tree_diameter(edges1)
    d2 = tree_diameter(edges2)
    return max(ceil_divide(d1, 2)+1+ceil_divide(d2, 2), d1, d2)


