def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

def singleDivisorTriplet(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def check(a, b, c):
        return sum((a+b+c)%x == 0 for x in (a, b, c)) == 1

    cnt = collections.Counter(nums)
    return 6*(sum(cnt[a]*cnt[b]*cnt[c] for a, b, c in itertools.combinations(cnt.keys(), 3) if check(a, b, c)) +
              sum(cnt[a]*(cnt[a]-1)//2*cnt[b] for a, b in itertools.permutations(cnt.keys(), 2) if check(a, a, b)))


