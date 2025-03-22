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

def countDaysTogether(self, arriveAlice, leaveAlice, arriveBob, leaveBob):
    """
    :type arriveAlice: str
    :type leaveAlice: str
    :type arriveBob: str
    :type leaveBob: str
    :rtype: int
    """
    NUMS = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    prefix = [0]*(len(NUMS)+1)
    for i in xrange(len(NUMS)):
        prefix[i+1] += prefix[i]+NUMS[i]

    def day(date):
        return prefix[int(date[:2])-1]+int(date[3:])

    return max(day(min(leaveAlice, leaveBob))-day(max(arriveAlice, arriveBob))+1, 0)


