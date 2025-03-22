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

def query(self, L, R):  # Time: O(logN), Space: O(N)
    def push(x):
        n = 2**self.H
        while n != 1:
            y = x // n
            if self.lazy[y] is not None:
                self.__apply(y*2, self.lazy[y])
                self.__apply(y*2 + 1, self.lazy[y])
                self.lazy[y] = None
            n //= 2

    result = None
    if L > R:
        return result

    L += self.N
    R += self.N
    push(L)
    push(R)
    while L <= R:
        if L & 1:  # is right child
            result = self.query_fn(result, self.tree[L])
            L += 1
        if R & 1 == 0:  # is left child
            result = self.query_fn(result, self.tree[R])
            R -= 1
        L //= 2
        R //= 2
    return result



