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

def minimumCost(self, nums, k, dist):
    """
    :type nums: List[int]
    :type k: int
    :type dist: int
    :rtype: int
    """
    sl1, sl2 = SortedList(), SortedList()
    mn, curr = float("inf"), 0
    for i in xrange(1, len(nums)):
        sl1.add(nums[i])
        curr += nums[i]
        if len(sl1) > k-1:
            curr -= sl1[-1]
            sl2.add(sl1.pop())
        if len(sl1)+len(sl2) > 1+dist:
            if sl2[0] <= nums[i-(1+dist)]:
                sl2.remove(nums[i-(1+dist)])
            else:
                sl1.remove(nums[i-(1+dist)])
                curr -= nums[i-(1+dist)]-sl2[0]
                sl1.add(sl2.pop(0))
        if len(sl1) == k-1:
            mn = min(mn, curr)
    return nums[0]+mn



