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

def equalizeWater(self, buckets, loss):
    """
    :type buckets: List[int]
    :type loss: int
    :rtype: float
    """
    def check(buckets, rate, x):
        return sum(b-x for b in buckets if b-x > 0)*rate >= sum(x-b for b in buckets if x-b > 0)

    EPS = 1e-5
    rate = (100-loss)/100.0
    left, right = float(min(buckets)), float(sum(buckets))/len(buckets)
    while right-left > EPS:
        mid = left + (right-left)/2
        if not check(buckets, rate, mid):
            right = mid
        else:
            left = mid
    return left


