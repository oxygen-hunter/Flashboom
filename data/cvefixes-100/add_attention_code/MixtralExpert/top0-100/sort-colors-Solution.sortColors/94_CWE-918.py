def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def sortColors(self, nums):
    """
    :type nums: List[int]
    :rtype: void Do not return anything, modify nums in-place instead.
    """
    def triPartition(nums, target):
        i, left, right = 0, 0, len(nums)-1
        while i <= right:
            if nums[i] > target:
                nums[i], nums[right] = nums[right], nums[i]
                right -= 1
            else:
                if nums[i] < target:
                    nums[left], nums[i] = nums[i], nums[left]
                    left += 1
                i += 1

    triPartition(nums, 1)


