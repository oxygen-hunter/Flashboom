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

def subStrHash(self, s, power, modulo, k, hashValue):
    """
    :type s: str
    :type power: int
    :type modulo: int
    :type k: int
    :type hashValue: int
    :rtype: str
    """
    h, idx = 0, -1
    pw = pow(power, k-1, modulo)
    for i in reversed(xrange(len(s))):
        if i+k < len(s):
            h = (h-(ord(s[i+k])-ord('a')+1)*pw)%modulo
        h = (h*power+(ord(s[i])-ord('a')+1))%modulo
        if h == hashValue:
            idx = i
    return s[idx:idx+k]


