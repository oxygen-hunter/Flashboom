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

def __iterative_backtracking(self):
    def conquer():
        if len(curr) == self.__combinationLength:
            return curr

    def prev_divide(c):
        curr.append(c)
    
    def divide(i):
        if len(curr) != self.__combinationLength:
            for j in reversed(xrange(i, len(self.__characters)-(self.__combinationLength-len(curr)-1))):
                stk.append(functools.partial(post_divide))
                stk.append(functools.partial(divide, j+1))
                stk.append(functools.partial(prev_divide, self.__characters[j]))
        stk.append(functools.partial(conquer))

    def post_divide():
        curr.pop()
        
    curr = []
    stk = [functools.partial(divide, 0)]
    while stk:
        result = stk.pop()()
        if result is not None:
            yield result



