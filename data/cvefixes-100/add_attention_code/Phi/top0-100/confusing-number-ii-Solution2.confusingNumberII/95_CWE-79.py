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

def confusingNumberII(self, n):
    """
    :type n: int
    :rtype: int
    """
    lookup = {"0":"0", "1":"1", "6":"9", "8":"8", "9":"6"}
    centers = {"0":"0", "1":"1", "8":"8"}
    def totalCount(n):  # count all numbers in the pattern of [01689]{1,len(n)} in the range of [0, n]
        s = str(n)
        total = 0 
        p = len(lookup)**(len(s)-1)
        for i in xrange(len(s)+1):
            if i == len(s):
                total += 1
                break
            smaller = sum(int(c < s[i]) for c in lookup.iterkeys())
            total += smaller * p
            if s[i] not in lookup:
                break
            p //= len(lookup)
        return total

    def validCountInLessLength(n):  # count unconfusing numbers in the pattern of [01689]{1,len(n)-1} in the range of [0, n]
        s = str(n)
        valid = 0
        total = len(centers)
        for i in xrange(1, len(s), 2):  # count unconfusing numbers for each odd length less than s
            if i == 1:
                valid += len(centers)
            else:
                valid += total * (len(lookup)-1)
                total *= len(lookup)
        total = 1
        for i in xrange(2, len(s), 2):  # count unconfusing numbers for each even length less than s
            valid += total * (len(lookup)-1)
            total *= len(lookup)
        return valid

    def validCountInFullLength(n):  # count unconfusing numbers in the pattern of [01689]{len(n)} in the range of [0, n]
        s = str(n)
        half_s = s[:(len(s)+1)//2]
        total = 0
        choices = centers if (len(s) % 2) else lookup
        p = int(len(lookup)**(len(half_s)-2) * len(choices))
        for i in xrange(len(half_s)):
            if i == len(half_s)-1:
                total += sum(int(c < half_s[i]) for c in choices.iterkeys() if len(s) != 2 or c != '0')
                if half_s[i] not in choices:
                    break
                tmp = list(half_s)+[lookup[half_s[i]] for i in reversed(xrange(len(half_s)-(len(s) % 2)))]
                total += int("".join(tmp)) <= n
                break
            smaller = sum(int(c < half_s[i]) for c in lookup.iterkeys() if i != 0 or c != '0')
            total += smaller * p
            if half_s[i] not in lookup:
                break
            p //= len(lookup)
        return total

    def f(n):  # count confusing numbers in the range of [0, n]
        return totalCount(n) - validCountInLessLength(n) - validCountInFullLength(n)

    return f(n) - f(0)  # f(0) is always 0 and could be ignored


