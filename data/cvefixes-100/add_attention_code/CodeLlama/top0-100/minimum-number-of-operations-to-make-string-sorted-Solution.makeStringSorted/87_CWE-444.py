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

def makeStringSorted(self, s):  # count of prev_permutation
    """
    :type s: str
    :rtype: int
    """
    def inverse(n, m):
        i = len(inv)
        while len(inv) <= n:  # lazy initialization
            inv.append(inv[m%i]*(m-m//i) % m)  # https://cp-algorithms.com/algebra/module-inverse.html
            i += 1
        return inv[n]

    MOD = 10**9+7
    count, result, comb_total = [0]*26, 0, 1
    for i in reversed(xrange(len(s))):
        num = ord(s[i])-ord('a') 
        count[num] += 1
        comb_total = (comb_total*(len(s)-i))*inverse(count[num], MOD)
        result = (result + (comb_total*sum(count[:num]))*inverse(len(s)-i, MOD)) % MOD
    return result


