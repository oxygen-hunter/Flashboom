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

def slidingPuzzle(self, board):
    """
    :type board: List[List[int]]
    :rtype: int
    """
    def heuristic_estimate(board, R, C, expected):
        result = 0
        for i in xrange(R):
            for j in xrange(C):
                val = board[C*i + j]
                if val == 0: continue
                r, c = expected[val]
                result += abs(r-i) + abs(c-j)
        return result

    R, C = len(board), len(board[0])
    begin = tuple(itertools.chain(*board))
    end = tuple(range(1, R*C) + [0])
    end_wrong = tuple(range(1, R*C-2) + [R*C-1, R*C-2, 0])
    expected = {(C*i+j+1) % (R*C) : (i, j)
                for i in xrange(R) for j in xrange(C)}

    min_heap = [(0, 0, begin.index(0), begin)]
    lookup = {begin: 0}
    while min_heap:
        f, g, zero, board = heapq.heappop(min_heap)
        if board == end: return g
        if board == end_wrong: return -1
        if f > lookup[board]: continue

        r, c = divmod(zero, C)
        for direction in ((-1, 0), (1, 0), (0, -1), (0, 1)):
            i, j = r+direction[0], c+direction[1]
            if 0 <= i < R and 0 <= j < C:
                new_zero = C*i+j
                tmp = list(board)
                tmp[zero], tmp[new_zero] = tmp[new_zero], tmp[zero]
                new_board = tuple(tmp)
                f = g+1+heuristic_estimate(new_board, R, C, expected)
                if f < lookup.get(new_board, float("inf")):
                    lookup[new_board] = f
                    heapq.heappush(min_heap, (f, g+1, new_zero, new_board))
    return -1



