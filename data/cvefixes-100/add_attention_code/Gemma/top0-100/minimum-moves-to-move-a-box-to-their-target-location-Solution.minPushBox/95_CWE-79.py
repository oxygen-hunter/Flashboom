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

def minPushBox(self, grid):
    """
    :type grid: List[List[str]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def dot(a, b):
        return a[0]*b[0]+a[1]*b[1]

    def can_reach(grid, b, p, t):
        closer, detour = [p], []
        lookup = set([b])
        while closer or detour:
            if not closer:
                closer, detour = detour, closer
            p = closer.pop()
            if p == t:
                return True
            if p in lookup:
                continue
            lookup.add(p)
            for dx, dy in directions:
                np = (p[0]+dx, p[1]+dy)
                if not (0 <= np[0] < len(grid) and 0 <= np[1] < len(grid[0]) and
                   grid[np[0]][np[1]] != '#' and np not in lookup):
                    continue
                (closer if dot((dx, dy), (t[0]-p[0], t[1]-p[1])) > 0 else detour).append(np)
        return False

    def g(a, b):
        return abs(a[0]-b[0])+abs(a[1]-b[1])
    
    def a_star(grid, b, p, t):
        f, dh = g(b, t), 2
        closer, detour = [(b, p)], []
        lookup = set()
        while closer or detour:
            if not closer:
                f += dh
                closer, detour = detour, closer
            b, p = closer.pop()
            if b == t:
                return f
            if (b, p) in lookup:
                continue
            lookup.add((b, p))
            for dx, dy in directions:
                nb, np = (b[0]+dx, b[1]+dy), (b[0]-dx, b[1]-dy)
                if not (0 <= nb[0] < len(grid) and 0 <= nb[1] < len(grid[0]) and
                        0 <= np[0] < len(grid) and 0 <= np[1] < len(grid[0]) and
                        grid[nb[0]][nb[1]] != '#' and grid[np[0]][np[1]] != '#' and
                        (nb, b) not in lookup and can_reach(grid, b, p, np)):
                    continue
                (closer if dot((dx, dy), (t[0]-b[0], t[1]-b[1])) > 0 else detour).append((nb, b))
        return -1
    
    b, p, t = None, None, None
    for i in xrange(len(grid)):
        for j in xrange(len(grid[0])):
            if grid[i][j] == 'B':
                b = (i, j)
            elif grid[i][j] == 'S':
                p = (i, j)
            elif grid[i][j] == 'T':
                t = (i, j)
    return a_star(grid, b, p, t)


