def change_profile(kobo_support, local_oauth_check, oauth_status, translations, languages):
    to_save = request.form.to_dict()
    current_user.random_books = 0
    if current_user.role_passwd() or current_user.role_admin():
        if to_save.get("password"):
            current_user.password = generate_password_hash(to_save["password"])
    try:
        if to_save.get("kindle_mail", current_user.kindle_mail) != current_user.kindle_mail:
            current_user.kindle_mail = valid_email(to_save["kindle_mail"])
        if to_save.get("email", current_user.email) != current_user.email:
            current_user.email = check_email(to_save["email"])
        if current_user.role_admin():
            if to_save.get("name", current_user.name) != current_user.name:
                # Query User name, if not existing, change
                current_user.name = check_username(to_save["name"])
        current_user.random_books = 1 if to_save.get("show_random") == "on" else 0
        if to_save.get("default_language"):
            current_user.default_language = to_save["default_language"]
        if to_save.get("locale"):
            current_user.locale = to_save["locale"]
        old_state = current_user.kobo_only_shelves_sync
        # 1 -> 0: nothing has to be done
        # 0 -> 1: all synced books have to be added to archived books, + currently synced shelfs which
        # don't have to be synced have to be removed (added to Shelf archive)
        current_user.kobo_only_shelves_sync = int(to_save.get("kobo_only_shelves_sync") == "on") or 0
        if old_state == 0 and current_user.kobo_only_shelves_sync == 1:
            kobo_sync_status.update_on_sync_shelfs(current_user.id)

    except Exception as ex:
        flash(str(ex), category="error")
        return render_title_template("user_edit.html",
                                     content=current_user,
                                     translations=translations,
                                     profile=1,
                                     languages=languages,
                                     title=_(u"%(name)s's profile", name=current_user.name),
                                     page="me",
                                     kobo_support=kobo_support,
                                     registered_oauth=local_oauth_check,
                                     oauth_status=oauth_status)

    val = 0
    for key, __ in to_save.items():
        if key.startswith('show'):
            val += int(key[5:])
    current_user.sidebar_view = val
    if to_save.get("Show_detail_random"):
        current_user.sidebar_view += constants.DETAIL_RANDOM

    try:
        ub.session.commit()
        flash(_(u"Profile updated"), category="success")
        log.debug(u"Profile updated")
    except IntegrityError:
        ub.session.rollback()
        flash(_(u"Found an existing account for this e-mail address"), category="error")
        log.debug(u"Found an existing account for this e-mail address")
    except OperationalError as e:
        ub.session.rollback()
        log.error("Database error: %s", e)
        flash(_(u"Database error: %(error)s.", error=e), category="error")

def reorderSpaces(self, text):
    """
    :type text: str
    :rtype: str
    """
    text = list(text)
    # count the spaces and words
    space_count, word_count = 0, 0
    for i, c in enumerate(text):
        if c == ' ':
            space_count += 1
        elif i == 0 or text[i-1] == ' ':
            word_count += 1

    # rearrange all the spaces to the right
    left, i = 0, 0
    while i < len(text):
        has_word = False
        while i < len(text) and text[i] != ' ':
            text[left], text[i] = text[i], text[left]
            left += 1
            i += 1
            has_word = True
        if has_word:
            left += 1  # keep one space
        i += 1

    # rearrange all the spaces to the left
    equal_count = space_count//(word_count-1) if word_count-1 > 0 else 0
    extra_count = space_count%(word_count-1) if word_count-1 > 0 else space_count
    right, i = len(text)-1-extra_count, len(text)-1
    while i >= 0:
        has_word = False
        while i >= 0 and text[i] != ' ':
            text[right], text[i] = text[i], text[right]
            right -= 1
            i -= 1
            has_word = True
        if has_word:
            right -= equal_count  # keep equal_count spaces
        i -= 1
    return "".join(text)


