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

def majorityElement(self, nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    k, n, cnts = 3, len(nums), collections.defaultdict(int)

    for i in nums:
        cnts[i] += 1
        # Detecting k items in cnts, at least one of them must have exactly
        # one in it. We will discard those k items by one for each.
        # This action keeps the same mojority numbers in the remaining numbers.
        # Because if x / n  > 1 / k is true, then (x - 1) / (n - k) > 1 / k is also true.
        if len(cnts) == k:
            for j in cnts.keys():
                cnts[j] -= 1
                if cnts[j] == 0:
                    del cnts[j]

    # Resets cnts for the following counting.
    for i in cnts.keys():
        cnts[i] = 0

    # Counts the occurrence of each candidate integer.
    for i in nums:
        if i in cnts:
            cnts[i] += 1

    # Selects the integer which occurs > [n / k] times.
    result = []
    for i in cnts.keys():
        if cnts[i] > n / k:
            result.append(i)

    return result



