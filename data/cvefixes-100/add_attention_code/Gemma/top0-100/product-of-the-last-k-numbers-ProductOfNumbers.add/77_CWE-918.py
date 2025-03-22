def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

def add(self, num):
    """
    :type num: int
    :rtype: None
    """
    if not num:
        self.__accu = [1]
        return
    self.__accu.append(self.__accu[-1]*num)             



