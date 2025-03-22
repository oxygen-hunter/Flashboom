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

def reformat(self, s):
    """
    :type s: str
    :rtype: str
    """
    def char_gen(start, end, count):
        for c in xrange(ord(start), ord(end)+1):
            c = chr(c)
            for i in xrange(count[c]):
                yield c
        yield ''

    count = collections.defaultdict(int)
    alpha_cnt = 0
    for c in s:
        count[c] += 1
        if c.isalpha():
            alpha_cnt += 1
    if abs(len(s)-2*alpha_cnt) > 1:
        return ""

    result = []
    it1, it2 = char_gen('a', 'z', count), char_gen('0', '9', count)
    if alpha_cnt < len(s)-alpha_cnt:
        it1, it2 = it2, it1
    while len(result) < len(s):
        result.append(next(it1))
        result.append(next(it2))
    return "".join(result)


