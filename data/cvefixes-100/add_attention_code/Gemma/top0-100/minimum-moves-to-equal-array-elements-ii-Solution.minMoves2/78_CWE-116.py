def prepare_plugin_docs_command(self, plugin_names, plugin_type=None, response_format=None,
                                snippet=False, playbook_dir=None, module_path=None):

    if response_format and response_format not in DocConfig._supported_response_formats:
        raise ConfigurationError("Invalid response_format {0}, valid value is one of either {1}".format(response_format,
                                                                                                        ", ".join(DocConfig._supported_response_formats)))

    if not isinstance(plugin_names, list):
        raise ConfigurationError("plugin_names should be of type list, instead received {0} of type {1}".format(plugin_names, type(plugin_names)))

    self._prepare_env(runner_mode=self.runner_mode)
    self.cmdline_args = []

    if response_format == 'json':
        self.cmdline_args.append('-j')

    if snippet:
        self.cmdline_args.append('-s')

    if plugin_type:
        self.cmdline_args.extend(['-t', plugin_type])

    if playbook_dir:
        self.cmdline_args.extend(['--playbook-dir', playbook_dir])

    if module_path:
        self.cmdline_args.extend(['-M', module_path])

    self.cmdline_args.append(" ".join(plugin_names))

    self.command = [self._ansible_doc_exec_path] + self.cmdline_args
    self._handle_command_wrap(self.execution_mode, self.cmdline_args)

def minMoves2(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def kthElement(nums, k):
        def PartitionAroundPivot(left, right, pivot_idx, nums):
            pivot_value = nums[pivot_idx]
            new_pivot_idx = left
            nums[pivot_idx], nums[right] = nums[right], nums[pivot_idx]
            for i in xrange(left, right):
                if nums[i] > pivot_value:
                    nums[i], nums[new_pivot_idx] = nums[new_pivot_idx], nums[i]
                    new_pivot_idx += 1

            nums[right], nums[new_pivot_idx] = nums[new_pivot_idx], nums[right]
            return new_pivot_idx

        left, right = 0, len(nums) - 1
        while left <= right:
            pivot_idx = randint(left, right)
            new_pivot_idx = PartitionAroundPivot(left, right, pivot_idx, nums)
            if new_pivot_idx == k:
                return nums[new_pivot_idx]
            elif new_pivot_idx > k:
                right = new_pivot_idx - 1
            else:  # new_pivot_idx < k.
                left = new_pivot_idx + 1

    median = kthElement(nums, len(nums)//2)
    return sum(abs(num - median) for num in nums)



