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

def shortestBeautifulSubstring(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: str
    """
    def check(r1, r2):
        if r1[1]-r1[0]+1 > r2[1]-r2[0]+1:
            return False
        if r1[1]-r1[0]+1 < r2[1]-r2[0]+1:
            return True
        for i, j in itertools.izip(xrange(r1[0], r1[1]+1), xrange(r2[0], r2[1]+1)):
            if s[i] != s[j]:
                return s[i] < s[j]
        return False

    result = []
    left = curr = 0
    for right in xrange(len(s)):
        curr += s[right] == '1'
        while curr == k+1:
            curr -= s[left] == '1'
            left += 1
        while left < len(s) and s[left] == '0':
            left += 1
        if curr == k:
            if not result or check([left, right], result):
                result = [left, right]
    return s[result[0]:result[1]+1] if result else ""


