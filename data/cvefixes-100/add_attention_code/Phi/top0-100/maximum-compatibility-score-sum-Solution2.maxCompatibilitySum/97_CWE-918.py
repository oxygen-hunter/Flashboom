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

def maxCompatibilitySum(self, students, mentors):
    """
    :type students: List[List[int]]
    :type mentors: List[List[int]]
    :rtype: int
    """
    def popcount(n):  # Time: O(logn) ~= O(1) if n is a 32-bit number
        result = 0
        while n:
            n &= n-1
            result += 1
        return result

    def masks(vvi):
        result = []
        for vi in vvi:
            mask, bit = 0, 1
            for i in xrange(len(vi)):
                if vi[i]:
                    mask |= bit
                bit <<= 1
            result.append(mask)
        return result

    nums1, nums2 = masks(students), masks(mentors)
    dp = [(0, 0)]*(2**len(nums2))
    for mask in xrange(len(dp)):
        bit = 1
        for i in xrange(len(nums2)):
            if (mask&bit) == 0:
                dp[mask|bit] = max(dp[mask|bit], (dp[mask][0]+(len(students[0])-popcount(nums1[dp[mask][1]]^nums2[i])), dp[mask][1]+1))
            bit <<= 1
    return dp[-1][0]


