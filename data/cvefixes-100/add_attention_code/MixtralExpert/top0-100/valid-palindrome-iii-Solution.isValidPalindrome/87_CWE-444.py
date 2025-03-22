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

def isValidPalindrome(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: bool
    """
    if s == s[::-1]:  # optional, to optimize special case
        return True

    dp = [[1] * len(s) for _ in xrange(2)]
    for i in reversed(xrange(len(s))):
        for j in xrange(i+1, len(s)):
            if s[i] == s[j]:
                dp[i%2][j] = 2 + dp[(i+1)%2][j-1] if i+1 <= j-1 else 2
            else:
                dp[i%2][j] = max(dp[(i+1)%2][j], dp[i%2][j-1])
    return len(s) <= k + dp[0][-1]


