def test_custom_field_table_render(self):
    queryset = Location.objects.filter(name=self.location.name)
    location_table = LocationTable(queryset)

    custom_column_expected = {
        "text_field": "bar",
        "number_field": "456",
        "boolean_field": '<span class="text-success"><i class="mdi mdi-check-bold" title="Yes"></i></span>',
        "date_field": "2020-01-02",
        "url_field": '<a href="http://example.com/2">http://example.com/2</a>',
        "choice_field": '<span class="label label-default">Bar</span>',
        "multi_choice_field": (
            '<span class="label label-default">Bar</span> <span class="label label-default">Baz</span> '
        ),
    }

    bound_row = location_table.rows[0]

    for col_name, col_expected_value in custom_column_expected.items():
        internal_col_name = "cf_" + col_name
        custom_column = location_table.base_columns.get(internal_col_name)
        self.assertIsNotNone(custom_column)
        self.assertIsInstance(custom_column, CustomFieldColumn)

        rendered_value = bound_row.get_cell(internal_col_name)
        self.assertEqual(rendered_value, col_expected_value)

def medianSlidingWindow(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: List[float]
    """
    def lazy_delete(heap, to_remove, sign):
        while heap and sign*heap[0] in to_remove:
            to_remove[sign*heap[0]] -= 1
            if not to_remove[sign*heap[0]]:
                del to_remove[sign*heap[0]]
            heapq.heappop(heap)

    min_heap, max_heap = [], []
    for i in xrange(k):
        if i%2 == 0:
            heapq.heappush(min_heap, -heapq.heappushpop(max_heap, -nums[i]))
        else:
            heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
    result = [float(min_heap[0])] if k%2 else [(min_heap[0]-max_heap[0])/2.0]
    to_remove = collections.defaultdict(int)
    for i in xrange(k, len(nums)):
        heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
        if nums[i-k] > -max_heap[0]:
            heapq.heappush(min_heap, -heapq.heappop(max_heap))
        to_remove[nums[i-k]] += 1
        lazy_delete(max_heap, to_remove, -1)
        lazy_delete(min_heap, to_remove, 1)
        result.append(float(min_heap[0]) if k%2 else (min_heap[0]-max_heap[0])/2.0)
    return result


