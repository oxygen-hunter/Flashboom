def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def dfs(self, nums, path, res):
    if not nums:
        res.append(path)

    for i in xrange(len(nums)):
        # e.g., [1, 2, 3]: 3! = 6 cases
        # idx -> nums, path
        # 0 -> [2, 3], [1] -> 0: [3], [1, 2] -> [], [1, 2, 3]
        #                  -> 1: [2], [1, 3] -> [], [1, 3, 2]
        #
        # 1 -> [1, 3], [2] -> 0: [3], [2, 1] -> [], [2, 1, 3]
        #                  -> 1: [1], [2, 3] -> [], [2, 3, 1]
        #
        # 2 -> [1, 2], [3] -> 0: [2], [3, 1] -> [], [3, 1, 2]
        #                  -> 1: [1], [3, 2] -> [], [3, 2, 1]
        self.dfs(nums[:i] + nums[i+1:], path + [nums[i]], res)


