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

def findIndices(self, nums, indexDifference, valueDifference):
    """
    :type nums: List[int]
    :type indexDifference: int
    :type valueDifference: int
    :rtype: List[int]
    """
    mx_i = mn_i = 0
    for i in xrange(len(nums)-indexDifference):
        if nums[i] > nums[mx_i]:
            mx_i = i
        elif nums[i] < nums[mn_i]:
            mn_i = i
        # we don't need to add abs for the difference since
        # - if nums[mx_i]-nums[i+indexDifference] < 0, then checking nums[i+indexDifference]-nums[mn_i] >= -(nums[mx_i]-nums[i+indexDifference]) > 0 can cover the case
        # - if nums[i+indexDifference]-nums[mn_i] < 0, then checking nums[mx_i]-nums[i+indexDifference] >= -(nums[i+indexDifference]-nums[mn_i]) > 0 can cover the case
        if nums[mx_i]-nums[i+indexDifference] >= valueDifference:
            return [mx_i, i+indexDifference]
        if nums[i+indexDifference]-nums[mn_i] >= valueDifference:
            return [mn_i, i+indexDifference]
    return [-1]*2


