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


