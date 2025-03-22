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

def __iterative_backtracking(self):
    def conquer():
        if len(curr) == self.__combinationLength:
            return curr

    def prev_divide(c):
        curr.append(c)
    
    def divide(i):
        if len(curr) != self.__combinationLength:
            for j in reversed(xrange(i, len(self.__characters)-(self.__combinationLength-len(curr)-1))):
                stk.append(functools.partial(post_divide))
                stk.append(functools.partial(divide, j+1))
                stk.append(functools.partial(prev_divide, self.__characters[j]))
        stk.append(functools.partial(conquer))

    def post_divide():
        curr.pop()
        
    curr = []
    stk = [functools.partial(divide, 0)]
    while stk:
        result = stk.pop()()
        if result is not None:
            yield result



