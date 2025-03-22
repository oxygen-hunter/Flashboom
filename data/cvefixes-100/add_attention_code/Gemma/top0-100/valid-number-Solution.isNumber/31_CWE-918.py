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

def isNumber(self, s):
    """
    :type s: str
    :rtype: bool
    """
    transition_table = [[-1,  0,  3,  1,  2, -1],     # next states for state 0
                        [-1,  8, -1,  1,  4,  5],     # next states for state 1
                        [-1, -1, -1,  4, -1, -1],     # next states for state 2
                        [-1, -1, -1,  1,  2, -1],     # next states for state 3
                        [-1,  8, -1,  4, -1,  5],     # next states for state 4
                        [-1, -1,  6,  7, -1, -1],     # next states for state 5
                        [-1, -1, -1,  7, -1, -1],     # next states for state 6
                        [-1,  8, -1,  7, -1, -1],     # next states for state 7
                        [-1,  8, -1, -1, -1, -1]]     # next states for state 8

    state = 0
    for char in s:
        inputType = InputType.INVALID
        if char.isspace():
            inputType = InputType.SPACE
        elif char == '+' or char == '-':
            inputType = InputType.SIGN
        elif char.isdigit():
            inputType = InputType.DIGIT
        elif char == '.':
            inputType = InputType.DOT
        elif char == 'e' or char == 'E':
            inputType = InputType.EXPONENT

        state = transition_table[state][inputType]

        if state == -1:
            return False

    return state == 1 or state == 4 or state == 7 or state == 8



