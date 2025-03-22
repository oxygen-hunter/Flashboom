def data_received(self, data):
    self._buffer += data
    # try to parse the incoming data
    while self._buffer:
        try:
            buf = Buffer(self._buffer)
            try:
                header = header_from_binary(buf)
            except NotEnoughData:
                logger.debug('Not enough data while parsing header from client, waiting for more')
                return
            if len(buf) < header.body_size:
                logger.debug('We did not receive enough data from client. Need %s got %s', header.body_size,
                             len(buf))
                return
            # we have a complete message
            self.messages.put_nowait((header, buf))
            self._buffer = self._buffer[(header.header_size + header.body_size):]
        except Exception:
            logger.exception('Exception raised while parsing message from client')
            return

def findAllRecipes(self, recipes, ingredients, supplies):
    """
    :type recipes: List[str]
    :type ingredients: List[List[str]]
    :type supplies: List[str]
    :rtype: List[str]
    """
    indegree = collections.defaultdict(int)
    adj = collections.defaultdict(list)
    for r, ingredient in itertools.izip(recipes, ingredients): 
        indegree[r] = len(ingredient)
        for ing in ingredient:
            adj[ing].append(r)
    result = []
    recipes = set(recipes)
    q = supplies
    while q: 
        new_q = []
        for u in q:
            if u in recipes:
                result.append(u)
            for v in adj[u]:
                indegree[v] -= 1
                if not indegree[v]:
                    new_q.append(v)
        q = new_q
    return result 


