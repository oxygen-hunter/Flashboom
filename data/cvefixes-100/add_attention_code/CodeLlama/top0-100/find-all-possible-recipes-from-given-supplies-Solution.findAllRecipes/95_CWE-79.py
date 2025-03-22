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

def findAllRecipes(self, recipes, ingredients, supplies):
    """
    :type recipes: List[str]
    :type ingredients: List[List[str]]
    :type supplies: List[str]
    :rtype: List[str]
    """
    indegree = collections.defaultdict(int)
    adj = collections.defaultdict(list)
    for r, ingredient in itertools.izip(recipes, ingredients): 
        indegree[r] = len(ingredient)
        for ing in ingredient:
            adj[ing].append(r)
    result = []
    recipes = set(recipes)
    q = supplies
    while q: 
        new_q = []
        for u in q:
            if u in recipes:
                result.append(u)
            for v in adj[u]:
                indegree[v] -= 1
                if not indegree[v]:
                    new_q.append(v)
        q = new_q
    return result 


