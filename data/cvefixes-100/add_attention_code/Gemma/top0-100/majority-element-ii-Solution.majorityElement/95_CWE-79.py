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

def majorityElement(self, nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    k, n, cnts = 3, len(nums), collections.defaultdict(int)

    for i in nums:
        cnts[i] += 1
        # Detecting k items in cnts, at least one of them must have exactly
        # one in it. We will discard those k items by one for each.
        # This action keeps the same mojority numbers in the remaining numbers.
        # Because if x / n  > 1 / k is true, then (x - 1) / (n - k) > 1 / k is also true.
        if len(cnts) == k:
            for j in cnts.keys():
                cnts[j] -= 1
                if cnts[j] == 0:
                    del cnts[j]

    # Resets cnts for the following counting.
    for i in cnts.keys():
        cnts[i] = 0

    # Counts the occurrence of each candidate integer.
    for i in nums:
        if i in cnts:
            cnts[i] += 1

    # Selects the integer which occurs > [n / k] times.
    result = []
    for i in cnts.keys():
        if cnts[i] > n / k:
            result.append(i)

    return result



