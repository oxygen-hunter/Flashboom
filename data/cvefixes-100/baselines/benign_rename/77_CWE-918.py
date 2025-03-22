    def benign_get_file(recipe):
        if not recipe.link:
            recipe.link = Dropbox.get_share_link(recipe)
            recipe.save()

        response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

        return io.BytesIO(response.content)