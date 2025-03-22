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

def countRoutes(self, locations, start, finish, fuel):
    """
    :type locations: List[int]
    :type start: int
    :type finish: int
    :type fuel: int
    :rtype: int
    """
    MOD = 10**9+7

    s, f = locations[start], locations[finish]
    locations.sort()
    start, finish = bisect.bisect_left(locations, s), bisect.bisect_left(locations, f)

    left = [[0]*(fuel+1) for _ in xrange(len(locations))]  # left[i][f], last move is toward left to location i by f fuel
    right = [[0]*(fuel+1) for _ in xrange(len(locations))]  # right[i][f], last move is toward right to location i by f fuel
    for f in xrange(1, fuel+1):
        for j in xrange(len(locations)-1):
            d = locations[j+1]-locations[j]
            if f > d:
                # left[j][f] = right[j+1][f-d(j, j+1)] + 2*right[j+2][f-d(j, j+2)] + ... + 2^(k-1)*right[j+k][f-d(j, j+k)]
                # => left[j+1][f] = (ight[j+2][f-d(j+1, j+2)] + 2*right[j+3][f-d(j+1, j+3)] + ... + 2^(k-2)*right[j+1+k-1][f-d(j+1, j+1+k-1)]
                # => left[j+1][f-d(j, j+1)] = right[j+2][f-d(j, j+2)] + 2*right[j+3][f-d(j, j+3)] + ... + 2^(k-2)*right[j+k][f-d(j, j+k)]
                # => left[j][f] = right[j+1][f-d(j, j+1)] + 2*left[j+1][f-d(j, j+1)]
                left[j][f] = (right[j+1][f-d] + 2*left[j+1][f-d] % MOD) % MOD
            elif f == d:
                left[j][f] = int(j+1 == start)
        for j in xrange(1, len(locations)):
            d = locations[j]-locations[j-1]
            if f > d:
                # right[j][f] = left[j-1][f-d(j, j-1)] + 2*left[j-2][f-d(j, j-2)] + ... + 2^(k-1)*left[j-k][f-d(j, j-k)]
                # => right[j-1][f] = left[j-2][f-d(j-1, j-2)] + 2*left[j-3][f-d(j-1, j-3)] + ... + 2^(k-2)*left[j-1-k+1][f-d(j-1, j-1-k+1)]
                # => right[j-1][f-d(j, j-1)] = left[j-2][f-d(j, j-2)] + 2*left[j-3][f-d(j, j-3)] + ... + 2^(k-2)*left[j-k][f-d(j, j-k)]
                # => right[j][f] = left[j-1][f-d(j, j-1)] + 2*right[j-1][f-d(j, j-1)]
                right[j][f] = (left[j-1][f-d] + 2*right[j-1][f-d] % MOD) % MOD
            elif f == d:
                right[j][f] = int(j-1 == start)
    result = int(start == finish)
    for f in xrange(1, fuel+1):
        result = ((result + left[finish][f]) % MOD + right[finish][f]) % MOD
    return result



