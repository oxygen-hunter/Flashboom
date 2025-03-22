def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

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


