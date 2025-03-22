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

def pacificAtlantic(self, matrix):
    """
    :type matrix: List[List[int]]
    :rtype: List[List[int]]
    """
    PACIFIC, ATLANTIC = 1, 2

    def pacificAtlanticHelper(matrix, x, y, prev_height, prev_val, visited, res):
        if (not 0 <= x < len(matrix)) or \
           (not 0 <= y < len(matrix[0])) or \
           matrix[x][y] < prev_height or \
           (visited[x][y] | prev_val) == visited[x][y]:
            return

        visited[x][y] |= prev_val
        if visited[x][y] == (PACIFIC | ATLANTIC):
            res.append((x, y))

        for d in [(0, -1), (0, 1), (-1, 0), (1, 0)]:
            pacificAtlanticHelper(matrix, x + d[0], y + d[1], matrix[x][y], visited[x][y], visited, res)

    if not matrix:
        return []

    res = []
    m, n = len(matrix),len(matrix[0])
    visited = [[0 for _ in xrange(n)] for _ in xrange(m)]

    for i in xrange(m):
        pacificAtlanticHelper(matrix, i, 0, float("-inf"), PACIFIC, visited, res)
        pacificAtlanticHelper(matrix, i, n - 1, float("-inf"), ATLANTIC, visited, res)
    for j in xrange(n):
        pacificAtlanticHelper(matrix, 0, j, float("-inf"), PACIFIC, visited, res)
        pacificAtlanticHelper(matrix, m - 1, j, float("-inf"), ATLANTIC, visited, res)

    return res



