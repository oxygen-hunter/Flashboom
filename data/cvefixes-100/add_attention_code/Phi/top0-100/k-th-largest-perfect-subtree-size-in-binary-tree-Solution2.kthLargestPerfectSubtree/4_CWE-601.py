def prepare(self, reactor, clock, hs):
    # build a replication server
    server_factory = ReplicationStreamProtocolFactory(hs)
    self.streamer = hs.get_replication_streamer()
    self.server = server_factory.buildProtocol(None)

    # Make a new HomeServer object for the worker
    self.reactor.lookups["testserv"] = "1.2.3.4"
    self.worker_hs = self.setup_test_homeserver(
        http_client=None,
        homeserver_to_use=GenericWorkerServer,
        config=self._get_worker_hs_config(),
        reactor=self.reactor,
    )

    # Since we use sqlite in memory databases we need to make sure the
    # databases objects are the same.
    self.worker_hs.get_datastore().db_pool = hs.get_datastore().db_pool

    self.test_handler = self._build_replication_data_handler()
    self.worker_hs._replication_data_handler = self.test_handler

    repl_handler = ReplicationCommandHandler(self.worker_hs)
    self.client = ClientReplicationStreamProtocol(
        self.worker_hs, "client", "test", clock, repl_handler,
    )

    self._client_transport = None
    self._server_transport = None

def kthLargestPerfectSubtree(self, root, k):
    """
    :type root: Optional[TreeNode]
    :type k: int
    :rtype: int
    """
    def nth_element(nums, left, n, right, compare=lambda a, b: a < b):
        def tri_partition(nums, left, right, target):
            i = left
            while i <= right:
                if compare(nums[i], target):
                    nums[i], nums[left] = nums[left], nums[i]
                    left += 1
                    i += 1
                elif compare(target, nums[i]):
                    nums[i], nums[right] = nums[right], nums[i]
                    right -= 1
                else:
                    i += 1
            return left, right

        while left <= right:
            pivot_idx = random.randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx])
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    def dfs(curr):
        if not curr:
            result.append(0)
            return
        dfs(curr.left)
        left = result[-1]
        dfs(curr.right)
        right = result[-1]
        result.append(left+right+1 if left == right != -1 else -1)

    result = []
    dfs(root)
    nth_element(result, 0, k-1, len(result)-1, lambda a, b: a > b)
    return result[k-1] if k-1 < len(result) and result[k-1] > 0 else -1


