def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
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



