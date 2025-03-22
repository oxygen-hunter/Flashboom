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

def stoneGameV(self, stoneValue):
    """
    :type stoneValue: List[int]
    :rtype: int
    """
    n = len(stoneValue)
    prefix = [0]
    for v in stoneValue:
        prefix.append(prefix[-1] + v)

    mid = [[0]*n for _ in xrange(n)]
    for l in xrange(1, n+1):
        for i in xrange(n-l+1):
            j = i+l-1
            p = i if l == 1 else mid[i][j-1]
            while prefix[p]-prefix[i] < prefix[j+1]-prefix[p]:
                p += 1  # Time: O(n^2) in total
            mid[i][j] = p
    
    rmq = [[0]*n for _ in xrange(n)]
    for i in xrange(n):
        rmq[i][i] = stoneValue[i]

    dp = [[0]*n for _ in xrange(n)]
    for l in xrange(2, n+1):
        for i in xrange(n-l+1):
            j = i+l-1
            p = mid[i][j]
            max_score = 0
            if prefix[p]-prefix[i] == prefix[j+1]-prefix[p]:
                max_score = max(rmq[i][p-1], rmq[j][p])
            else:
                if i <= p-2:
                    max_score = max(max_score, rmq[i][p-2])
                if p <= j:
                    max_score = max(max_score, rmq[j][p])
            dp[i][j] = max_score
            rmq[i][j] = max(rmq[i][j-1], (prefix[j+1]-prefix[i]) + max_score)
            rmq[j][i] = max(rmq[j][i+1], (prefix[j+1]-prefix[i]) + max_score)
    return dp[0][n-1]


