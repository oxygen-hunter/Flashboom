def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

def findSmallestInteger(self, nums, value):
    """
    :type nums: List[int]
    :type value: int
    :rtype: int
    """
    cnt = collections.Counter(x%value for x in nums)
    for i in xrange(len(nums)+1):
        if not cnt[i%value]:
            return i
        cnt[i%value] -= 1


