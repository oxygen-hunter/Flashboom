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

def squareFreeSubsets(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def linear_sieve_of_eratosthenes(n):  # Time: O(n), Space: O(n)
        primes = []
        spf = [-1]*(n+1)  # the smallest prime factor
        for i in xrange(2, n+1):
            if spf[i] == -1:
                spf[i] = i
                primes.append(i)
            for p in primes:
                if i*p > n or p > spf[i]:
                    break
                spf[i*p] = p
        return primes

    MAX_NUM = max(nums)
    PRIMES = linear_sieve_of_eratosthenes(MAX_NUM)
    MASKS = [0]*(MAX_NUM+1)
    for x in xrange(MAX_NUM+1):
        y = x
        for i, p in enumerate(PRIMES):
            if y%p:
                continue
            if y%p**2 == 0:
                MASKS[x] = 0
                break
            MASKS[x] |= (1<<i)
            y //= p
    MOD = 10**9+7

    cnt = collections.Counter(nums)
    arr = [x for x in cnt.iterkeys() if x != 1]
    dp = [[-1]*(1<<len(PRIMES)) for i in xrange(len(arr))]
    def memoization(i, mask):
        if i == len(arr):
            return 1
        if dp[i][mask] == -1:
            dp[i][mask] = memoization(i+1, mask)
            if MASKS[arr[i]] and (MASKS[arr[i]]&mask) == MASKS[arr[i]]:
                dp[i][mask] = (dp[i][mask]+cnt[arr[i]]*memoization(i+1, mask^MASKS[arr[i]]))%MOD
        return dp[i][mask]

    return (memoization(0, (1<<len(PRIMES))-1)*pow(2, cnt[1], MOD)-1)%MOD if 1 in cnt else (memoization(0, (1<<len(PRIMES))-1)-1)%MOD


