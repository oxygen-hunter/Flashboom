def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

def minOperations(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    lookup = [False]*k
    for i in reversed(xrange(len(nums))):
        if nums[i] > len(lookup) or lookup[nums[i]-1]:
            continue
        lookup[nums[i]-1] = True
        k -= 1
        if not k:
            break
    return len(nums)-i


