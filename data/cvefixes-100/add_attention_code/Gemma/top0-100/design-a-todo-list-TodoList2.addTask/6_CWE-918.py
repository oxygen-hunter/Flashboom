def add_security_headers(resp):
    resp.headers['Content-Security-Policy'] = "default-src 'self'" + ''.join([' '+host for host in config.config_trustedhosts.strip().split(',')]) + " 'unsafe-inline' 'unsafe-eval'; font-src 'self' data:; img-src 'self' data:"
    if request.endpoint == "editbook.edit_book" or config.config_use_google_drive:
        resp.headers['Content-Security-Policy'] += " *"
    elif request.endpoint == "web.read_book":
        resp.headers['Content-Security-Policy'] += " blob:;style-src-elem 'self' blob: 'unsafe-inline';"
    resp.headers['X-Content-Type-Options'] = 'nosniff'
    resp.headers['X-Frame-Options'] = 'SAMEORIGIN'
    resp.headers['X-XSS-Protection'] = '1; mode=block'
    resp.headers['Strict-Transport-Security'] = 'max-age=31536000;'
    return resp

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



