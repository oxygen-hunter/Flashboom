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

def maximumGain(self, s, x, y):
    """
    :type s: str
    :type x: int
    :type y: int
    :rtype: int
    """
    def score(s, a, x):
        i = result = 0
        for j in xrange(len(s)):
            s[i] = s[j]
            i += 1
            if i >= 2 and s[i-2:i] == a:
                i -= 2
                result += x
        s[:] = s[:i]
        return result
            
    s, a, b = list(s), list("ab"), list("ba")
    if x < y:
        x, y = y, x
        a, b = b, a
    return score(s, a, x) + score(s, b, y)


