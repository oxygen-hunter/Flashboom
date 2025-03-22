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

def searchRange(self, nums, target):
    """
    :type nums: List[int]
    :type target: int
    :rtype: List[int]
    """
    def binarySearch(n, check):  # usually use
        left, right = 0, n-1  # search in [0, n-1], return n if not found
        while left <= right:
            mid = left + (right-left)//2
            if check(mid):
                right = mid-1
            else:
                left = mid+1
        return left  # or return right+1

    def binarySearch2(n, check):  # frequently use
        left, right = 0, n  # search in [0, n), return n if not found
        while left < right:
            mid = left + (right-left)//2
            if check(mid):
                right = mid
            else:
                left = mid+1
        return left  # or return right

    def binarySearch3(n, check):  # never use
        left, right = -1, n-1  # search in (-1, n-1], return n if not found
        while left < right:
            mid = right - (right-left)//2
            if check(mid):
                right = mid-1
            else:
                left = mid
        return left+1  # or return right+1

    def binarySearch4(n, check):  # sometimes use
        left, right = -1, n  # search in (-1, n), return n if not found
        while right-left >= 2:
            mid = left + (right-left)//2
            if check(mid):
                right = mid
            else:
                left = mid
        return left+1  # or return right

    # Find the first idx where nums[idx] >= target
    left = binarySearch(len(nums), lambda i: nums[i] >= target)
    if left == len(nums) or nums[left] != target:
        return [-1, -1]
    # Find the first idx where nums[idx] > target
    right = binarySearch(len(nums), lambda i: nums[i] > target)
    return [left, right-1]


