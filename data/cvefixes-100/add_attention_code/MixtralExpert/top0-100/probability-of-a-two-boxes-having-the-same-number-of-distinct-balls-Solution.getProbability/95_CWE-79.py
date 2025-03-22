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

def getProbability(self, balls):
    """
    :type balls: List[int]
    :rtype: float
    """
    def nCrs(n):  # Time: O(n), Space: O(1)
        c = 1
        for k in xrange(n+1):
            yield c
            c *= n-(k+1)+1
            c //= k+1
    
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if n-r < r:
            return nCr(n, n-r)
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c
    
    dp = collections.defaultdict(int)
    dp[0, 0] = 1  # dp[i, j] is the number of ways with number difference i and color difference j
    for n in balls:  # O(k) times
        new_dp = collections.defaultdict(int)
        for (ndiff, cdiff), count in dp.iteritems():  # O(k^2 * n) times
            for k, new_count in enumerate(nCrs(n)):  # O(n) times
                new_ndiff = ndiff+(k-(n-k))
                new_cdiff = cdiff-1 if k == 0 else (cdiff+1 if k == n else cdiff)
                new_dp[new_ndiff, new_cdiff] += count*new_count
        dp = new_dp
    total = sum(balls)
    return float(dp[0, 0])/nCr(total, total//2)


