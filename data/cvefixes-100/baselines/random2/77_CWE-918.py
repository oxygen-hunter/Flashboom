def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

def stoneGameVIII(self, stones):
    """
    :type stones: List[int]
    :rtype: int
    """
    for i in xrange(len(stones)-1):
        stones[i+1] += stones[i]
    return reduce(lambda curr, i: max(curr, stones[i]-curr), reversed(xrange(1, len(stones)-1)), stones[-1])


