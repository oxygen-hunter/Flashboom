def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

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


