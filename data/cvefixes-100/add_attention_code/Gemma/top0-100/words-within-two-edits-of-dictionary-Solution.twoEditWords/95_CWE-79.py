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

def twoEditWords(self, queries, dictionary):
    """
    :type queries: List[str]
    :type dictionary: List[str]
    :rtype: List[str]
    """
    MOD = (1<<64)-59  # largest 64-bit prime
    BASE = 113
    POW = [1]
    def add(a, b):
        return (a+b)%MOD

    def mult(a, b):
        return (a*b)%MOD

    def pow(i):
        while not (i < len(POW)):
            POW.append(mult(POW[-1], BASE))
        return POW[i]

    lookup = set()
    for w in dictionary:
        h = reduce(lambda h, i: add(h, mult(ord(w[i])-ord('a'), pow(i))), xrange(len(w)), 0)
        for i, c in enumerate(w):
            for x in string.ascii_lowercase:
                if x == c:
                    continue
                lookup.add(add(h, mult(ord(x)-ord(c), pow(i))))
    result = []
    for w in queries:
        h = reduce(lambda h, i: add(h, mult(ord(w[i])-ord('a'), pow(i))), xrange(len(w)), 0)
        for i, c in enumerate(w):
            for x in string.ascii_lowercase:
                if x == c:
                    continue
                if add(h, mult(ord(x)-ord(c), pow(i))) in lookup:
                    break
            else:
                continue
            result.append(w)
            break
    return result



