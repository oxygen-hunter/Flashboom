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

def maximumNumberOfOnes(self, width, height, sideLength, maxOnes):
    """
    :type width: int
    :type height: int
    :type sideLength: int
    :type maxOnes: int
    :rtype: int
    """
    if width < height:
        width, height = height, width

    # 1. split matrix by SxS tiles
    # 2. split each SxS tile into four parts
    #    (r, c), (r, S-c), (S-r, c), (S-r, S-c)
    # 3. for each count of tile part in matrix is
    #    (R+1)*(C+1), (R+1)*C, R*(C+1), R*C (already in descending order)
    # 4. fill one into matrix by tile part of which count is in descending order
    #    until number of ones in a tile comes to maxOnes
    # 
    # ps. area of a tile and its count in matrix are as follows:
    #
    #  |<---- c ---->|<-- S-c -->|
    #  ^             |           |
    #  |             |           |
    #  r (R+1)*(C+1) |  (R+1)*C  |
    #  |             |           |
    #  v             |           |
    #  ---------------------------
    #  ^             |           |
    #  |             |           |
    #  S-r  R*(C+1)  |   R*C     |
    #  |             |           |
    #  v             |           |
    #  ---------------------------
    #

    R, r = divmod(height, sideLength)
    C, c = divmod(width, sideLength)
    assert(R <= C)
    area_counts = [(r*c, (R+1)*(C+1)), \
                   (r*(sideLength-c), (R+1)*C), \
                   ((sideLength-r)*c, R*(C+1)), \
                   ((sideLength-r)*(sideLength-c), R*C)]
    result = 0
    for area, count in area_counts:
        area = min(maxOnes, area)
        result += count*area
        maxOnes -= area
        if not maxOnes:
            break
    return result


