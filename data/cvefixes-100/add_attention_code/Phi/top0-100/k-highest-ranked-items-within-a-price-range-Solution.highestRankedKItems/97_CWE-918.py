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

def highestRankedKItems(self, grid, pricing, start, k):
    """
    :type grid: List[List[int]]
    :type pricing: List[int]
    :type start: List[int]
    :type k: int
    :rtype: List[List[int]]
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def nth_element(nums, n, left=0, compare=lambda a, b: a < b):
        def tri_partition(nums, left, right, target, compare):
            mid = left
            while mid <= right:
                if nums[mid] == target:
                    mid += 1
                elif compare(nums[mid], target):
                    nums[left], nums[mid] = nums[mid], nums[left]
                    left += 1
                    mid += 1
                else:
                    nums[mid], nums[right] = nums[right], nums[mid]
                    right -= 1
            return left, right

        right = len(nums)-1
        while left <= right:
            pivot_idx = random.randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx], compare)
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    def get_val(x):
        return (lookup[x[0]][x[1]], grid[x[0]][x[1]], x[0], x[1])

    result = []
    q = [start]
    lookup = [[-1]*len(grid[0]) for _ in xrange(len(grid))]
    d = lookup[start[0]][start[1]] = 0
    while q:
        if len(result) >= k:
            if len(result) > k:
                nth_element(result, k-1, compare=lambda a, b: get_val(a) < get_val(b))
                result = result[:k]
            break
        new_q = []
        for r, c in q:
            if pricing[0] <= grid[r][c] <= pricing[1]:
                result.append([r, c])
            for dr, dc in directions:
                nr, nc = r+dr, c+dc
                if not (0 <= nr < len(grid) and 0 <= nc < len(grid[0]) and grid[nr][nc] and lookup[nr][nc] == -1):
                    continue
                lookup[nr][nc] = d+1
                new_q.append((nr, nc))
        q = new_q
        d += 1
    result.sort(key=lambda x: get_val(x))
    return result


