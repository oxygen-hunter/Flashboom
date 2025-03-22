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

def nextPalindrome(self, num):
    """
    :type num: str
    :rtype: str
    """
    def next_permutation(nums, begin, end):
        def reverse(nums, begin, end):
            left, right = begin, end-1
            while left < right:
                nums[left], nums[right] = nums[right], nums[left]
                left += 1
                right -= 1

        k, l = begin-1, begin
        for i in reversed(xrange(begin, end-1)):
            if nums[i] < nums[i+1]:
                k = i
                break
        else:
            reverse(nums, begin, end)
            return False
        for i in reversed(xrange(k+1, end)):
            if nums[i] > nums[k]:
                l = i
                break
        nums[k], nums[l] = nums[l], nums[k]
        reverse(nums, k+1, end)
        return True
    
    nums = list(num)
    if not next_permutation(nums, 0, len(nums)//2):
        return ""
    for i in xrange(len(nums)//2):
        nums[-1-i] = nums[i]
    return "".join(nums)


