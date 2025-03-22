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

def shortestPathAllKeys(self, grid):
    """
    :type grid: List[str]
    :rtype: int
    """
    directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

    def bfs(grid, source, locations):
        r, c = locations[source]
        lookup = [[False]*(len(grid[0])) for _ in xrange(len(grid))]
        lookup[r][c] = True
        q = collections.deque([(r, c, 0)])
        dist = {}
        while q:
            r, c, d = q.popleft()
            if source != grid[r][c] != '.':
                dist[grid[r][c]] = d
                continue
            for direction in directions:
                cr, cc = r+direction[0], c+direction[1]
                if not ((0 <= cr < len(grid)) and
                        (0 <= cc < len(grid[cr]))):
                    continue
                if grid[cr][cc] != '#' and not lookup[cr][cc]:
                    lookup[cr][cc] = True
                    q.append((cr, cc, d+1))
        return dist

    locations = {place: (r, c)
                 for r, row in enumerate(grid)
                 for c, place in enumerate(row)
                 if place not in '.#'}
    dists = {place: bfs(grid, place, locations) for place in locations}

    # Dijkstra's algorithm
    min_heap = [(0, '@', 0)]
    best = collections.defaultdict(lambda: collections.defaultdict(
                                               lambda: float("inf")))
    best['@'][0] = 0
    target_state = 2**sum(place.islower() for place in locations)-1
    while min_heap:
        cur_d, place, state = heapq.heappop(min_heap)
        if best[place][state] < cur_d:
            continue
        if state == target_state:
            return cur_d
        for dest, d in dists[place].iteritems():
            next_state = state
            if dest.islower():
                next_state |= (1 << (ord(dest)-ord('a')))
            elif dest.isupper():
                if not (state & (1 << (ord(dest)-ord('A')))):
                    continue
            if cur_d+d < best[dest][next_state]:
                best[dest][next_state] = cur_d+d
                heapq.heappush(min_heap, (cur_d+d, dest, next_state))
    return -1



