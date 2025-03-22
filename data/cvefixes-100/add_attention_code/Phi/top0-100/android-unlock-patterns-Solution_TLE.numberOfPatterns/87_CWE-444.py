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

def numberOfPatterns(self, m, n):
    """
    :type m: int
    :type n: int
    :rtype: int
    """
    def merge(used, i):
        return used | (1 << i)

    def contain(used, i):
        return bool(used & (1 << i))

    def convert(i, j):
        return 3 * i + j

    def numberOfPatternsHelper(m, n, level, used, i):
        number = 0
        if level > n:
            return number

        if m <= level <= n:
            number += 1

        x1, y1 = divmod(i, 3)
        for j in xrange(9):
            if contain(used, j):
                continue

            x2, y2 = divmod(j, 3)
            if ((x1 == x2 and abs(y1 - y2) == 2) or
                (y1 == y2 and abs(x1 - x2) == 2) or
                (abs(x1 - x2) == 2 and abs(y1 - y2) == 2)) and \
               not contain(used,
                           convert((x1 + x2) // 2, (y1 + y2) // 2)):
                    continue

            number += numberOfPatternsHelper(m, n, level + 1, merge(used, j), j)

        return number

    number = 0
    # 1, 3, 7, 9
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 0), 0)
    # 2, 4, 6, 8
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 1), 1)
    # 5
    number += numberOfPatternsHelper(m, n, 1, merge(0, 4), 4)
    return number



