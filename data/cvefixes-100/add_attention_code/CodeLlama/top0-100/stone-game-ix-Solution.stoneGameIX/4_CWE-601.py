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

def stoneGameIX(self, stones):
    """
    :type stones: List[int]
    :rtype: bool
    """
    count = collections.Counter(x%3 for x in stones)
    if count[0]%2 == 0:
        # iff both counts are not zero, then alice takes the least one at first, the remains are deterministic for bob to lose:
        # - assumed count[1] is the least one:
        #   1(,1,2)*,2,(,2)* => bob loses
        #            ^
        # - assumed count[2] is the least one:
        #   2(,2,1)*,1,(,1)* => bob loses
        #            ^
        return count[1] and count[2]
    # iff abs(count[1] - count[2]) >= 3, then alice takes the most one at first, the remains are deterministic for bob to lose:
    # - assumed count[1] is the most one
    #   1(,1,2)*,0,1(,2,1)*,1,(,1)* => bob loses
    #                       ^
    #   1(,1,2)*,1,0,1,(,1)* => bob loses
    #                ^
    # - assumed count[2] is the most one
    #   2(,2,1)*,0,2(,1,2)*,2,(,2)* => bob loses
    #                       ^
    #   2(,2,1)*,2,0,2,(,2)* => bob loses
    #                ^
    return abs(count[1]-count[2]) >= 3  


