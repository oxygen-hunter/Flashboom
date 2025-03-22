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

def maximumSumSubsequence(self, nums, queries):
    """
    :type nums: List[int]
    :type queries: List[List[int]]
    :rtype: int
    """
    MOD = 10**9+7
    L0R0, L1R0, L0R1, L1R1 = range(4)
    # Template:
    # https://github.com/kamyu104/LeetCode-Solutions/blob/master/Python/block-placement-queries.py
    class SegmentTree(object):
        def __init__(self, N,
                    build_fn=lambda _: None,
                    query_fn=lambda x, y: y if x is None else x if y is None else max(x, y),
                    update_fn=lambda x: x):
            self.tree = [None]*(1<<((N-1).bit_length()+1))
            self.base = len(self.tree)>>1
            self.query_fn = query_fn
            self.update_fn = update_fn
            for i in xrange(self.base, self.base+N):
                self.tree[i] = build_fn(i-self.base)
            for i in reversed(xrange(1, self.base)):
                self.tree[i] = query_fn(self.tree[i<<1], self.tree[(i<<1)+1])

        def update(self, i, h):
            x = self.base+i
            self.tree[x] = self.update_fn(h)
            while x > 1:
                x >>= 1
                self.tree[x] = self.query_fn(self.tree[x<<1], self.tree[(x<<1)+1])

        def query(self, L, R):
            L += self.base
            R += self.base
            left = right = None
            while L <= R:
                if L & 1:
                    left = self.query_fn(left, self.tree[L])
                    L += 1
                if R & 1 == 0:
                    right = self.query_fn(self.tree[R], right)
                    R -= 1
                L >>= 1
                R >>= 1
            return self.query_fn(left, right)
    
    def build(i):
        return [max(nums[i], 0), 0, 0, 0]
    
    def query(x, y):
        if x is None:
            return y
        if y is None:
            return x
        return [max(x[L0R1]+y[L1R0], x[L0R0]+y[L1R0], x[L0R1]+y[L0R0]),
                max(x[L1R1]+y[L1R0], x[L1R0]+y[L1R0], x[L1R1]+y[L0R0]),
                max(x[L0R1]+y[L1R1], x[L0R0]+y[L1R1], x[L0R1]+y[L0R1]),
                max(x[L1R1]+y[L1R1], x[L1R0]+y[L1R1], x[L1R1]+y[L0R1])]

    st = SegmentTree(len(nums), build_fn=build, query_fn=query)
    result = 0
    for i, x in queries:
        st.update(i, [max(x, 0), 0, 0, 0])
        result = (result+max(st.tree[1]))%MOD
    return result


