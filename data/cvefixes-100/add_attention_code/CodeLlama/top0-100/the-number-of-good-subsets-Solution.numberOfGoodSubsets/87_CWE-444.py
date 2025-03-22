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

def numberOfGoodSubsets(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def sieve_of_eratosthenes(n):  # Time: O(n * log(logn)), Space: O(n)
        if n < 2:
            return []
        primes = [2]
        is_prime = [True]*((n+1)//2)
        for i in xrange(1, len(is_prime)):
            if not is_prime[i]:
                continue
            primes.append(2*i+1)
            for j in xrange(2*i*(i+1), len(is_prime), (2*i+1)):
                is_prime[j] = False
        return primes

    def to_mask(primes, x):
        mask, basis = 0, 1
        for p in primes:
            if x%p == 0:
                mask |= basis
            basis <<= 1
        return mask

    MOD = 10**9+7
    primes = sieve_of_eratosthenes(max(nums))
    dp = [0]*(1<<len(primes))  # dp[i] = the number of different good subsets of which the total product equals to the product of the primes in bitset i
    dp[0] = 1
    cnts = collections.Counter(nums)
    for x, cnt in cnts.iteritems():
        if x == 1 or any(x%(p*p) == 0 for p in primes if p*p <= x):
            continue
        mask = to_mask(primes, x)
        for i in xrange(len(dp)-1):
            if i&mask:
                continue
            dp[i|mask] = (dp[i|mask]+cnt*dp[i])%MOD
    return (pow(2, cnts[1], MOD))*(reduce(lambda total, x: (total+x)%MOD, dp, 0)-1)%MOD


