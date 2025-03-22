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

def isSolvable(self, words, result):
    """
    :type words: List[str]
    :type result: str
    :rtype: bool
    """
    def backtracking(words, result, i, j, carry, lookup, used):
        if j == len(result):
            return carry == 0

        if i != len(words):
            if j >= len(words[i]) or words[i][j] in lookup:
                return backtracking(words, result, i+1, j, carry, lookup, used)     
            for val in xrange(10):
                if val in used or (val == 0 and j == len(words[i])-1):
                    continue
                lookup[words[i][j]] = val
                used.add(val)
                if backtracking(words, result, i+1, j, carry, lookup, used):
                    return True
                used.remove(val)
                del lookup[words[i][j]]
            return False

        carry, val = divmod(carry + sum(lookup[w[j]] for w in words if j < len(w)), 10)
        if result[j] in lookup:
            return val == lookup[result[j]] and \
                   backtracking(words, result, 0, j+1, carry, lookup, used)
        if val in used or (val == 0 and j == len(result)-1):
            return False
        lookup[result[j]] = val
        used.add(val)
        if backtracking(words, result, 0, j+1, carry, lookup, used):
            return True
        used.remove(val)
        del lookup[result[j]]
        return False
    
    return backtracking([w[::-1] for w in words], result[::-1], 0, 0, 0, {}, set())


