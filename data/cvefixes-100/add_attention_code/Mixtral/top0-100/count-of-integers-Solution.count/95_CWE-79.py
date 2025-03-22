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

def count(self, num1, num2, min_sum, max_sum):
    """
    :type num1: str
    :type num2: str
    :type min_sum: int
    :type max_sum: int
    :rtype: int
    """
    MOD = 10**9+7
    def f(x):
        dp = [[0]*(max_sum+1) for _ in xrange(2)]
        dp[0][0] = dp[1][0] = 1
        for i in reversed(xrange(len(x))):
            new_dp = [[0]*(max_sum+1) for _ in xrange(2)]
            for t in xrange(2):
                for total in xrange(max_sum+1):
                    for d in xrange(min((int(x[i]) if t else 9), total)+1):
                        new_dp[t][total] = (new_dp[t][total]+dp[int(t and d == int(x[i]))][total-d])%MOD
            dp = new_dp
        return reduce(lambda x, y: (x+y)%MOD, (dp[1][total] for total in xrange(min_sum, max_sum+1)))

    return (f(num2)-f(str(int(num1)-1)))%MOD


