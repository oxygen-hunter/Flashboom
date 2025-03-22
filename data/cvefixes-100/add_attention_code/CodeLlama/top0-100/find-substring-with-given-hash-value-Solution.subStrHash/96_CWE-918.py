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

def subStrHash(self, s, power, modulo, k, hashValue):
    """
    :type s: str
    :type power: int
    :type modulo: int
    :type k: int
    :type hashValue: int
    :rtype: str
    """
    h, idx = 0, -1
    pw = pow(power, k-1, modulo)
    for i in reversed(xrange(len(s))):
        if i+k < len(s):
            h = (h-(ord(s[i+k])-ord('a')+1)*pw)%modulo
        h = (h*power+(ord(s[i])-ord('a')+1))%modulo
        if h == hashValue:
            idx = i
    return s[idx:idx+k]


