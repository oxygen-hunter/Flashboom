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

def dieSimulator(self, n, rollMax):
    """
    :type n: int
    :type rollMax: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    def sum_mod(array):
        return reduce(lambda x, y: (x+y)%MOD, array)

    dp = [[1] + [0]*(rollMax[i]-1) for i in xrange(6)]  # 0-indexed
    for _ in xrange(n-1):
        new_dp = [[0]*rollMax[i] for i in xrange(6)]
        for i in xrange(6):
            for k in xrange(rollMax[i]):
                for j in xrange(6):
                    if i == j:
                        if k < rollMax[i]-1:  # 0-indexed
                            new_dp[j][k+1] = (new_dp[j][k+1]+dp[i][k])%MOD
                    else:
                        new_dp[j][0] = (new_dp[j][0]+dp[i][k])%MOD
        dp = new_dp
    return sum_mod(sum_mod(row) for row in dp)


