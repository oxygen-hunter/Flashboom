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

def shortestCommonSupersequence(self, str1, str2):
    """
    :type str1: str
    :type str2: str
    :rtype: str
    """
    dp = [[0 for _ in xrange(len(str2)+1)] for _ in xrange(2)]
    bt = [[None for _ in xrange(len(str2)+1)] for _ in xrange(len(str1)+1)]
    for i, c in enumerate(str1):
        bt[i+1][0] = (i, 0, c)
    for j, c in enumerate(str2):
        bt[0][j+1] = (0, j, c)
    for i in xrange(len(str1)):
        for j in xrange(len(str2)):
            if dp[i % 2][j+1] > dp[(i+1) % 2][j]:
                dp[(i+1) % 2][j+1] = dp[i % 2][j+1]
                bt[i+1][j+1] = (i, j+1, str1[i])
            else:
                dp[(i+1) % 2][j+1] = dp[(i+1) % 2][j]
                bt[i+1][j+1] = (i+1, j, str2[j])
            if str1[i] != str2[j]:
                continue
            if dp[i % 2][j]+1 > dp[(i+1) % 2][j+1]:
                dp[(i+1) % 2][j+1] = dp[i % 2][j]+1
                bt[i+1][j+1] = (i, j, str1[i])
    
    i, j = len(str1), len(str2)
    result = []
    while i != 0 or j != 0:
        i, j, c = bt[i][j]
        result.append(c)
    result.reverse()
    return "".join(result)


