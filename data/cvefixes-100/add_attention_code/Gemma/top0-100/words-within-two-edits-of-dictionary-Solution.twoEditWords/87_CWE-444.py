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

def twoEditWords(self, queries, dictionary):
    """
    :type queries: List[str]
    :type dictionary: List[str]
    :rtype: List[str]
    """
    MOD = (1<<64)-59  # largest 64-bit prime
    BASE = 113
    POW = [1]
    def add(a, b):
        return (a+b)%MOD

    def mult(a, b):
        return (a*b)%MOD

    def pow(i):
        while not (i < len(POW)):
            POW.append(mult(POW[-1], BASE))
        return POW[i]

    lookup = set()
    for w in dictionary:
        h = reduce(lambda h, i: add(h, mult(ord(w[i])-ord('a'), pow(i))), xrange(len(w)), 0)
        for i, c in enumerate(w):
            for x in string.ascii_lowercase:
                if x == c:
                    continue
                lookup.add(add(h, mult(ord(x)-ord(c), pow(i))))
    result = []
    for w in queries:
        h = reduce(lambda h, i: add(h, mult(ord(w[i])-ord('a'), pow(i))), xrange(len(w)), 0)
        for i, c in enumerate(w):
            for x in string.ascii_lowercase:
                if x == c:
                    continue
                if add(h, mult(ord(x)-ord(c), pow(i))) in lookup:
                    break
            else:
                continue
            result.append(w)
            break
    return result



