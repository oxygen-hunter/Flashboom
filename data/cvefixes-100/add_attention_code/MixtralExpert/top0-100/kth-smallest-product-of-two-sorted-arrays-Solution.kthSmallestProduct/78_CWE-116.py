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


