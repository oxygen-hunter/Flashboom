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

def removeInvalidParentheses(self, s):
    """
    :type s: str
    :rtype: List[str]
    """
    # Calculate the minimum left and right parantheses to remove
    def findMinRemove(s):
        left_removed, right_removed = 0, 0
        for c in s:
            if c == '(':
                left_removed += 1
            elif c == ')':
                if not left_removed:
                    right_removed += 1
                else:
                    left_removed -= 1
        return (left_removed, right_removed)

    # Check whether s is valid or not.
    def isValid(s):
        sum = 0
        for c in s:
            if c == '(':
                sum += 1
            elif c == ')':
                sum -= 1
            if sum < 0:
                return False
        return sum == 0

    def removeInvalidParenthesesHelper(start, left_removed, right_removed):
        if left_removed == 0 and right_removed == 0:
            tmp = ""
            for i, c in enumerate(s):
                if i not in removed:
                    tmp += c
            if isValid(tmp):
                res.append(tmp)
            return

        for i in xrange(start, len(s)):
            if right_removed == 0 and left_removed > 0 and s[i] == '(':
                if i == start or s[i] != s[i - 1]:  # Skip duplicated.
                    removed[i] = True
                    removeInvalidParenthesesHelper(i + 1, left_removed - 1, right_removed)
                    del removed[i]
            elif right_removed > 0 and s[i] == ')':
                if i == start or s[i] != s[i - 1]:  # Skip duplicated.
                    removed[i] = True
                    removeInvalidParenthesesHelper(i + 1, left_removed, right_removed - 1)
                    del removed[i]

    res, removed = [], {}
    (left_removed, right_removed) = findMinRemove(s)
    removeInvalidParenthesesHelper(0, left_removed, right_removed)
    return res



