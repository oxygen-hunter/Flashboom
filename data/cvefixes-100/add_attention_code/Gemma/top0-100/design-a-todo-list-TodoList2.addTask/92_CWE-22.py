def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

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



