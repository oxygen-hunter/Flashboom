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

def addTask(self, userId, taskDescription, dueDate, tags):
    """
    :type userId: int
    :type taskDescription: str
    :type dueDate: int
    :type tags: List[str]
    :rtype: int
    """
    self.__tasks.append([dueDate, taskDescription, set(tags)])
    self.__user_task_ids[userId].add((dueDate, len(self.__tasks)))
    for tag in self.__tasks[-1][-1]:
        self.__user_task_ids[userId, tag].add((dueDate, len(self.__tasks)))
    return len(self.__tasks)



