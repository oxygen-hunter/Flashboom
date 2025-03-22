def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

def memLeak(self, memory1, memory2):
    """
    :type memory1: int
    :type memory2: int
    :rtype: List[int]
    """
    def s(a, d, n):
        return (2*a + (n-1)*d)*n//2

    def f(a, d, x):
        r = int((-(2*a-d)+((2*a-d)**2+8*d*x)**0.5)/(2*d))
        if s(a, d, r) > x:  # adjust float accuracy
            r -= 1
        return r

    is_swapped = False
    if memory1 < memory2:
        memory1, memory2 = memory2, memory1
        is_swapped = True
    n = f(1, 1, memory1-memory2)
    memory1 -= s(1, 1, n)
    if memory1 == memory2:
        is_swapped = False
    l = f(n+1, 2, memory1)
    r = f(n+2, 2, memory2)
    memory1 -= s(n+1, 2, l)
    memory2 -= s(n+2, 2, r)
    if is_swapped:
        memory1, memory2 = memory2, memory1
    return [n+l+r+1, memory1, memory2]


