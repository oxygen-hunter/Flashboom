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

def putMarbles(self, weights, k):
    """
    :type weights: List[int]
    :type k: int
    :rtype: int
    """
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

    for i in xrange(len(weights)-1):
        weights[i] += weights[i+1]
    weights.pop()
    result = 0
    nth_element(weights, (k-1)-1, compare=lambda a, b: a > b)
    result += sum(weights[i] for i in xrange(k-1))
    nth_element(weights, (k-1)-1)
    result -= sum(weights[i] for i in xrange(k-1))
    return result


