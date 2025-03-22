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

def maxGcdSum(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def gcd(a, b):
        while b:
            a, b = b, a%b
        return a

    def binary_search_right(left, right, check):
        while left <= right:
            mid = left + (right-left)//2
            if not check(mid):
                right = mid-1
            else:
                left = mid+1
        return right

    # RMQ - Sparse Table
    # Template: https://github.com/kamyu104/GoogleCodeJam-Farewell-Rounds/blob/main/Round%20D/genetic_sequences2.py3
    # Time:  ctor:  O(NlogN) * O(fn)
    #        query: O(fn)
    # Space: O(NlogN)
    class SparseTable(object):
        def __init__(self, arr, fn):
            self.fn = fn
            self.bit_length = [0]
            n = len(arr)
            k = n.bit_length()-1  # log2_floor(n)
            for i in xrange(k+1):
                self.bit_length.extend(i+1 for _ in xrange(min(1<<i, (n+1)-len(self.bit_length))))
            self.st = [[0]*n for _ in xrange(k+1)]
            self.st[0] = arr[:]
            for i in xrange(1, k+1):  # Time: O(NlogN) * O(fn)
                for j in xrange((n-(1<<i))+1):
                    self.st[i][j] = fn(self.st[i-1][j], self.st[i-1][j+(1<<(i-1))])
    
        def query(self, L, R):  # Time: O(fn)
            i = self.bit_length[R-L+1]-1  # log2_floor(R-L+1)
            return self.fn(self.st[i][L], self.st[i][R-(1<<i)+1])
    
    prefix = [0]*(len(nums)+1)
    for i, x in enumerate(nums):
        prefix[i+1] = prefix[i]+x
    result = 0
    rmq = SparseTable(nums, gcd)
    for left, x in enumerate(nums):
        right = left
        while right < len(nums):  # O(logr) times
            g = rmq.query(left, right)
            right = binary_search_right(right, len(nums)-1, lambda x: rmq.query(left, x) >= g)  # Time: O(logn) * O(logr)
            if right-left+1 >= k:
                result = max(result, (prefix[right+1]-prefix[left])*g)
            right += 1
    return result


