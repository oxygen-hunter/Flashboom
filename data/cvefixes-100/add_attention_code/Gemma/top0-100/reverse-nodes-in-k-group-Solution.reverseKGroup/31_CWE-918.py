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

def reverseKGroup(self, head, k):
    dummy = ListNode(-1)
    dummy.next = head

    cur, cur_dummy = head, dummy
    length = 0

    while cur:
        next_cur = cur.next
        length = (length + 1) % k

        if length == 0:
            next_dummy = cur_dummy.next
            self.reverse(cur_dummy, cur.next)
            cur_dummy = next_dummy

        cur = next_cur

    return dummy.next



