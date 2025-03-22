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

def reconstructMatrix(self, upper, lower, colsum):
    """
    :type upper: int
    :type lower: int
    :type colsum: List[int]
    :rtype: List[List[int]]
    """
    upper_matrix, lower_matrix = [0]*len(colsum), [0]*len(colsum)
    for i in xrange(len(colsum)):
        upper_matrix[i] = int(upper > 0 and colsum[i] != 0)
        lower_matrix[i] = colsum[i]-upper_matrix[i]
        upper -= upper_matrix[i]
        lower -= lower_matrix[i]
    return [upper_matrix, lower_matrix] if upper == lower == 0 else []


