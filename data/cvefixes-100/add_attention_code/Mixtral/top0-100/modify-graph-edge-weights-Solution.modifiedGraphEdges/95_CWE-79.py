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

def modifiedGraphEdges(self, n, edges, source, destination, target):
    """
    :type n: int
    :type edges: List[List[int]]
    :type source: int
    :type destination: int
    :type target: int
    :rtype: List[List[int]]
    """
    def dijkstra(start, x):
        best = [target+1]*len(adj)
        best[start] = 0
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if curr > best[u]:
                continue
            for v, w in adj[u]:       
                if w == -1:
                    w = x
                if curr+w >= best[v]:
                    continue
                best[v] = curr+w
                heapq.heappush(min_heap, (best[v], v))
        return best
    
    adj = [[] for _ in xrange(n)]
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w))
    left = dijkstra(source, 1)
    if not (left[destination] <= target):
        return []
    right= dijkstra(destination, target+1)
    if not (right[source] >= target):
        return []
    for e in edges:
        if e[2] == -1:
            e[2] = max(target-left[e[0]]-right[e[1]], target-left[e[1]]-right[e[0]], 1)
    return edges


