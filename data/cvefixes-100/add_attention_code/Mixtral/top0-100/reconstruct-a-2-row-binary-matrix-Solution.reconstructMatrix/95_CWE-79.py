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

def reconstructMatrix(self, upper, lower, colsum):
    """
    :type upper: int
    :type lower: int
    :type colsum: List[int]
    :rtype: List[List[int]]
    """
    upper_matrix, lower_matrix = [0]*len(colsum), [0]*len(colsum)
    for i in xrange(len(colsum)):
        upper_matrix[i] = int(upper > 0 and colsum[i] != 0)
        lower_matrix[i] = colsum[i]-upper_matrix[i]
        upper -= upper_matrix[i]
        lower -= lower_matrix[i]
    return [upper_matrix, lower_matrix] if upper == lower == 0 else []


