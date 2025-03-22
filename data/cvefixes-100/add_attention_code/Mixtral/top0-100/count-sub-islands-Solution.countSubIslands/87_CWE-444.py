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

def countSubIslands(self, grid1, grid2):
    """
    :type grid1: List[List[int]]
    :type grid2: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def dfs(grid1, grid2, i, j):
        if not (0 <= i < len(grid2) and
                0 <= j < len(grid2[0]) and
                grid2[i][j] == 1):
            return 1
        grid2[i][j] = 0
        result = grid1[i][j]
        for di, dj in directions:
            result &= dfs(grid1, grid2, i+di, j+dj)
        return result
        
    return sum(dfs(grid1, grid2, i, j) for i in xrange(len(grid2)) for j in xrange(len(grid2[0])) if grid2[i][j])


