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

def isNumber(self, s):
    """
    :type s: str
    :rtype: bool
    """
    transition_table = [[-1,  0,  3,  1,  2, -1],     # next states for state 0
                        [-1,  8, -1,  1,  4,  5],     # next states for state 1
                        [-1, -1, -1,  4, -1, -1],     # next states for state 2
                        [-1, -1, -1,  1,  2, -1],     # next states for state 3
                        [-1,  8, -1,  4, -1,  5],     # next states for state 4
                        [-1, -1,  6,  7, -1, -1],     # next states for state 5
                        [-1, -1, -1,  7, -1, -1],     # next states for state 6
                        [-1,  8, -1,  7, -1, -1],     # next states for state 7
                        [-1,  8, -1, -1, -1, -1]]     # next states for state 8

    state = 0
    for char in s:
        inputType = InputType.INVALID
        if char.isspace():
            inputType = InputType.SPACE
        elif char == '+' or char == '-':
            inputType = InputType.SIGN
        elif char.isdigit():
            inputType = InputType.DIGIT
        elif char == '.':
            inputType = InputType.DOT
        elif char == 'e' or char == 'E':
            inputType = InputType.EXPONENT

        state = transition_table[state][inputType]

        if state == -1:
            return False

    return state == 1 or state == 4 or state == 7 or state == 8



