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

def kthSmallestProduct(self, nums1, nums2, k):
    """
    :type nums1: List[int]
    :type nums2: List[int]
    :type k: int
    :rtype: int
    """
    def check(nums1, nums2, k, neg_cnt, target):
        cnt = 0
        left, right = 0, len(nums2)-1
        direction = reversed if target >= 0 else lambda x: x
        for i in direction(xrange(neg_cnt)):
            while left < len(nums2) and nums1[i]*nums2[left] > target:
                left += 1
            cnt += (len(nums2)-1)-left+1
        direction = (lambda x: x) if target >= 0 else reversed
        for i in direction(xrange(neg_cnt, len(nums1))): 
            if nums1[i] == 0: 
                if target >= 0:
                    cnt += len(nums2)
                continue
            while right >= 0 and nums1[i]*nums2[right] > target:
                right -= 1
            cnt += right-0+1
        return cnt >= k

    neg_cnt = sum(x < 0 for x in nums1)
    left = min(nums1[i]*nums2[j] for i in (0, -1) for j in (0, -1))
    right = max(nums1[i]*nums2[j] for i in (0, -1) for j in (0, -1))
    while left <= right:
        mid = left + (right-left)//2
        if check(nums1, nums2, k, neg_cnt, mid):
            right = mid-1
        else:
            left = mid+1
    return left


