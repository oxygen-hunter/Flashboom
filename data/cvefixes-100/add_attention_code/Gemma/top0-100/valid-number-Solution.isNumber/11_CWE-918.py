def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

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



