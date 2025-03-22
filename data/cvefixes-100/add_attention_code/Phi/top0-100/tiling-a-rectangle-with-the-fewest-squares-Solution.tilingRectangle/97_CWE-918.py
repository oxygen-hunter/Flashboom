def add_objects(db_book_object, db_object, db_session, db_type, add_elements):
    changed = False
    if db_type == 'languages':
        db_filter = db_object.lang_code
    elif db_type == 'custom':
        db_filter = db_object.value
    else:
        db_filter = db_object.name
    for add_element in add_elements:
        # check if a element with that name exists
        db_element = db_session.query(db_object).filter(db_filter == add_element).first()
        # if no element is found add it
        if db_type == 'author':
            new_element = db_object(add_element, helper.get_sorted_author(add_element.replace('|', ',')), "")
        elif db_type == 'series':
            new_element = db_object(add_element, add_element)
        elif db_type == 'custom':
            new_element = db_object(value=add_element)
        elif db_type == 'publisher':
            new_element = db_object(add_element, None)
        else:  # db_type should be tag or language
            new_element = db_object(add_element)
        if db_element is None:
            changed = True
            db_session.add(new_element)
            db_book_object.append(new_element)
        else:
            db_element = create_objects_for_addition(db_element, add_element, db_type)
            changed = True
            # add element to book
            changed = True
            db_book_object.append(db_element)
    return changed

def tilingRectangle(self, n, m):
    """
    :type n: int
    :type m: int
    :rtype: int
    """
    def find_next(board):
        for i in xrange(len(board)):
            for j in xrange(len(board[0])):
                if not board[i][j]:
                    return i, j
        return -1, -1

    def find_max_length(board, i, j):
        max_length = 1
        while i+max_length-1 < len(board) and \
              j+max_length-1 < len(board[0]):
            for r in xrange(i, i+max_length-1):
                if board[r][j+max_length-1]:
                    return max_length-1
            for c in xrange(j, j+max_length):
                if board[i+max_length-1][c]:
                    return max_length-1
            max_length += 1
        return max_length-1

    def fill(board, i, j, length, val):
        for r in xrange(i, i+length):
            for c in xrange(j, j+length):
                board[r][c] = val

    def backtracking(board, count, result):
        if count >= result[0]:  # pruning
            return
        i, j = find_next(board)
        if (i, j) == (-1, -1):  # finished
            result[0] = min(result[0], count)
            return
        max_length = find_max_length(board, i, j)
        for k in reversed(xrange(1, max_length+1)):
            fill(board, i, j, k, 1)
            backtracking(board, count+1, result)
            fill(board, i, j, k, 0)

    if m > n:
        return self.tilingRectangle(m, n)
    board = [[0]*m for _ in xrange(n)]
    result = [float("inf")]
    backtracking(board, 0, result)
    return result[0]


