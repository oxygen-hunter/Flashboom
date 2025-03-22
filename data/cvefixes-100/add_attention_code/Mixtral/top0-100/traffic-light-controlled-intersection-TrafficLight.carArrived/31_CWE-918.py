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

def carArrived(self, carId, roadId, direction, turnGreen, crossCar):
    """
    :type roadId: int --> // ID of the car
    :type carId: int --> // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
    :type direction: int --> // Direction of the car
    :type turnGreen: method --> // Use turnGreen() to turn light to green on current road
    :type crossCar: method --> // Use crossCar() to make car cross the intersection
    :rtype: void
    """
    with self.__l:
        if self.__light != roadId:
            self.__light = roadId
            turnGreen()
        crossCar()


