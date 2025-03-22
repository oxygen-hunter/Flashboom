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

def longestSubsequenceRepeatedK(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: str
    """
    def check(s, k, curr):
        if not curr:
            return True
        i = 0
        for c in s:
            if c != curr[i]:
                continue
            i += 1
            if i != len(curr):
                continue
            i = 0
            k -= 1
            if not k:
                return True
        return False

    def backtracking(s, k, curr, cnts, result):
        if not check(s, k, curr):
            return
        if len(curr) > len(result):
            result[:] = curr
        for c in reversed(string.ascii_lowercase):
            if cnts[c] < k:
                continue
            cnts[c] -= k
            curr.append(c)
            backtracking(s, k, curr, cnts, result)
            curr.pop()
            cnts[c] += k
                
    cnts = collections.Counter(s)
    new_s = []
    for c in s:
        if cnts[c] < k:
            continue
        new_s.append(c)
    result =[]
    backtracking(new_s, k, [], cnts, result)
    return "".join(result)


