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

def countStrobogrammaticUntil(self, num,  can_start_with_0):
    if can_start_with_0 and num in self.cache:
        return self.cache[num]

    count = 0
    if len(num) == 1:
        for c in ['0', '1', '8']:
            if num[0] >= c:
                count += 1
        self.cache[num] = count
        return count

    for key, val in self.lookup.iteritems():
        if can_start_with_0 or key != '0':
            if num[0] > key:
                if len(num) == 2:  # num is like "21"
                    count += 1
                else:  # num is like "201"
                    count += self.countStrobogrammaticUntil('9' * (len(num) - 2), True)
            elif num[0] == key:
                if len(num) == 2:  # num is like 12".
                    if num[-1] >= val:
                        count += 1
                else:
                    if num[-1] >= val:  # num is like "102".
                        count += self.countStrobogrammaticUntil(self.getMid(num), True)
                    elif (self.getMid(num) != '0' * (len(num) - 2)):  # num is like "110".
                        count += self.countStrobogrammaticUntil(self.getMid(num), True) - \
                                 self.isStrobogrammatic(self.getMid(num))

    if not can_start_with_0: # Sum up each length.
        for i in xrange(len(num) - 1, 0, -1):
            count += self.countStrobogrammaticByLength(i)
    else:
        self.cache[num] = count

    return count



