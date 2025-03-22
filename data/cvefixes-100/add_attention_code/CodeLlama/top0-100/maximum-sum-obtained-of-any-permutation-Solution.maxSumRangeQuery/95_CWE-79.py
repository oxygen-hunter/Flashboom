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

def maxSumRangeQuery(self, nums, requests):
    """
    :type nums: List[int]
    :type requests: List[List[int]]
    :rtype: int
    """
    def addmod(a, b, mod):  # avoid overflow in other languages
        a %= mod
        b %= mod
        if mod-a <= b:
            b -= mod
        return a+b
    
    def mulmod(a, b, mod):  # avoid overflow in other languages
        a %= mod
        b %= mod
        if a < b:
            a, b = b, a
        result = 0
        while b > 0:
            if b%2 == 1:
                result = addmod(result, a, mod)
            a = addmod(a, a, mod)
            b //= 2
        return result

    MOD = 10**9+7

    count = [0]*len(nums)
    for start, end in requests:
        count[start] += 1
        if end+1 < len(count):
            count[end+1] -= 1
    for i in xrange(1, len(count)):
        count[i] += count[i-1]
    nums.sort()
    count.sort()
    result = 0
    for i, (num, c) in enumerate(itertools.izip(nums, count)):
        # result = addmod(result, mulmod(num, c, MOD), MOD)
        result = (result+num*c)%MOD
    return result


