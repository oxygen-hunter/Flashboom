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

def countSubstrings(self, s, t):
    """
    :type s: str
    :type t: str
    :rtype: int
    """
    def count(i, j):  # for each possible alignment, count the number of substrs that differ by 1 char
        result = left_cnt = right_cnt = 0  # left and right consecutive same counts relative to the different char
        for k in xrange(min(len(s)-i, len(t)-j)):
            right_cnt += 1
            if s[i+k] != t[j+k]:
                left_cnt, right_cnt = right_cnt, 0
                # prev_i = i+k-prev+1
            result += left_cnt  # target substrs are [s[left_i+c:i+k+1] for c in xrange(left_cnt)]
        return result

    return sum(count(i, 0) for i in xrange(len(s))) + \
           sum(count(0, j) for j in xrange(1, len(t)))


