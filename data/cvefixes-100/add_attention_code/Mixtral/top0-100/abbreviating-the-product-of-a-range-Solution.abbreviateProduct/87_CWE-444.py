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

def abbreviateProduct(self, left, right):
    """
    :type left: int
    :type right: int
    :rtype: str
    """
    PREFIX_LEN = SUFFIX_LEN = 5
    MOD = 10**(PREFIX_LEN+SUFFIX_LEN)
    curr, zeros = 1, 0
    abbr = False
    for i in xrange(left, right+1):
        curr *= i
        while not curr%10:
            curr //= 10
            zeros += 1
        q, curr = divmod(curr, MOD)
        if q:
            abbr = True
    if not abbr:
        return "%se%s" % (curr, zeros)
    decimal = reduce(lambda x, y: (x+y)%1, (math.log10(i) for i in xrange(left, right+1)))
    prefix = str(int(10**(decimal+(PREFIX_LEN-1))))
    suffix = str(curr % 10**SUFFIX_LEN).zfill(SUFFIX_LEN)
    return "%s...%se%s" % (prefix, suffix, zeros)


