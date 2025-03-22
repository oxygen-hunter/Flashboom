def profile():
    languages = calibre_db.speaking_language()
    translations = babel.list_translations() + [LC('en')]
    kobo_support = feature_support['kobo'] and config.config_kobo_sync
    if feature_support['oauth'] and config.config_login_type == 2:
        oauth_status = get_oauth_status()
        local_oauth_check = oauth_check
    else:
        oauth_status = None
        local_oauth_check = {}

    if request.method == "POST":
        change_profile(kobo_support, local_oauth_check, oauth_status, translations, languages)
    return render_title_template("user_edit.html",
                                 translations=translations,
                                 profile=1,
                                 languages=languages,
                                 content=current_user,
                                 kobo_support=kobo_support,
                                 title=_(u"%(name)s's profile", name=current_user.name),
                                 page="me",
                                 registered_oauth=local_oauth_check,
                                 oauth_status=oauth_status)

def isEscapePossible(self, blocked, source, target):
    """
    :type blocked: List[List[int]]
    :type source: List[int]
    :type target: List[int]
    :rtype: bool
    """
    R, C = 10**6, 10**6
    directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

    def bfs(blocks, source, target):
        max_area_surrounded_by_blocks = len(blocks)*(len(blocks)-1)//2
        lookup = set([source])
        if len(lookup) > max_area_surrounded_by_blocks:
            return True
        q = collections.deque([source])
        while q:
            source = q.popleft()
            if source == target:
                return True
            for direction in directions:
                nr, nc = source[0]+direction[0], source[1]+direction[1]
                if not ((0 <= nr < R) and
                        (0 <= nc < C) and 
                        (nr, nc) not in lookup and
                        (nr, nc) not in blocks):
                    continue
                lookup.add((nr, nc))
                if len(lookup) > max_area_surrounded_by_blocks:
                    return True
                q.append((nr, nc))
        return False
    
    return bfs(set(map(tuple, blocked)), tuple(source), tuple(target)) and \
           bfs(set(map(tuple, blocked)), tuple(target), tuple(source))


