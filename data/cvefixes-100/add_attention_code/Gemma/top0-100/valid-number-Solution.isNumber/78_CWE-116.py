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

def isNumber(self, s):
    """
    :type s: str
    :rtype: bool
    """
    transition_table = [[-1,  0,  3,  1,  2, -1],     # next states for state 0
                        [-1,  8, -1,  1,  4,  5],     # next states for state 1
                        [-1, -1, -1,  4, -1, -1],     # next states for state 2
                        [-1, -1, -1,  1,  2, -1],     # next states for state 3
                        [-1,  8, -1,  4, -1,  5],     # next states for state 4
                        [-1, -1,  6,  7, -1, -1],     # next states for state 5
                        [-1, -1, -1,  7, -1, -1],     # next states for state 6
                        [-1,  8, -1,  7, -1, -1],     # next states for state 7
                        [-1,  8, -1, -1, -1, -1]]     # next states for state 8

    state = 0
    for char in s:
        inputType = InputType.INVALID
        if char.isspace():
            inputType = InputType.SPACE
        elif char == '+' or char == '-':
            inputType = InputType.SIGN
        elif char.isdigit():
            inputType = InputType.DIGIT
        elif char == '.':
            inputType = InputType.DOT
        elif char == 'e' or char == 'E':
            inputType = InputType.EXPONENT

        state = transition_table[state][inputType]

        if state == -1:
            return False

    return state == 1 or state == 4 or state == 7 or state == 8



