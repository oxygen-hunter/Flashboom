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

def subStrHash(self, s, power, modulo, k, hashValue):
    """
    :type s: str
    :type power: int
    :type modulo: int
    :type k: int
    :type hashValue: int
    :rtype: str
    """
    h, idx = 0, -1
    pw = pow(power, k-1, modulo)
    for i in reversed(xrange(len(s))):
        if i+k < len(s):
            h = (h-(ord(s[i+k])-ord('a')+1)*pw)%modulo
        h = (h*power+(ord(s[i])-ord('a')+1))%modulo
        if h == hashValue:
            idx = i
    return s[idx:idx+k]


