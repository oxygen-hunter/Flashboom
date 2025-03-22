def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

def countEven(self, num):
    """
    :type num: int
    :rtype: int
    """
    def parity(x):
        result = 0
        while x:
            result += x%10
            x //= 10
        return result%2

    return sum(parity(x) == 0 for x in xrange(1, num+1))



