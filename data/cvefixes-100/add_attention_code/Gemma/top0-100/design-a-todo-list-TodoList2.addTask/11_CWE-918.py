def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

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



