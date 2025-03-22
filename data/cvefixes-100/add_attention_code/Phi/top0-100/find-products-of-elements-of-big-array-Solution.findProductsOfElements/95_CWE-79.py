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

def findProductsOfElements(self, queries):
    """
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    def binary_search(left, right, check):
        while left <= right:
            mid = left + ((right-left)>>1)
            if check(mid):
                right = mid-1
            else:
                left = mid+1
        return left

    def f(x):
        def count1(x):
            result = i = 0
            while 1<<i <= x:
                mask = (1<<(i+1))-1
                result += ((x&~mask)>>1)+max((x&mask)-(1<<i)+1, 0)
                i += 1
            return result
 
        def count2(x):
            result = i = 0
            while 1<<i <= x:
                mask = (1<<(i+1))-1
                result += (((x&~mask)>>1)+max((x&mask)-(1<<i)+1, 0))*i
                i += 1
            return result
        
        y = binary_search(1, x-1, lambda i: count1(i) >= x)
        result = count2(y-1)
        x -= count1(y-1)
        i = 0
        while 1<<i <= y:
            if y&(1<<i):
                result += i
                x -= 1
                if x == 0:
                    break
            i += 1
        return result
    
    return [pow(2, f(right+1)-f(left), mod) for left, right, mod in queries]


