def _moderate(request, pk, field_name, to_value, action=None, message=None):
    topic = get_object_or_404(Topic, pk=pk)

    if is_post(request):
        count = (
            Topic.objects
            .filter(pk=pk)
            .exclude(**{field_name: to_value})
            .update(**{
                field_name: to_value,
                'reindex_at': timezone.now()}))

        if count and action is not None:
            Comment.create_moderation_action(
                user=request.user,
                topic=topic,
                action=action)

        if message is not None:
            messages.info(request, message)

        return redirect(request.POST.get(
            'next', topic.get_absolute_url()))

    return render(
        request=request,
        template_name='spirit/topic/moderate.html',
        context={'topic': topic})

def minimumCost(self, target, words, costs):
    """
    :type target: str
    :type words: List[str]
    :type costs: List[int]
    :rtype: int
    """
    INF = float("inf")
    class Trie(object):
        def __init__(self):
            self.__nodes = []
            self.__mns = []
            self.__new_node()
        
        def __new_node(self):
            self.__nodes.append([-1]*26)
            self.__mns.append(INF)
            return len(self.__nodes)-1

        def add(self, w, c):
            curr = 0
            for x in w:
                x = ord(x)-ord('a')
                if self.__nodes[curr][x] == -1:
                    self.__nodes[curr][x] = self.__new_node()
                curr = self.__nodes[curr][x]
            self.__mns[curr] = min(self.__mns[curr], c)
        
        def query(self, i):
            curr = 0
            for j in xrange(i, len(target)):
                x = ord(target[j])-ord('a')
                if self.__nodes[curr][x] == -1:
                    break
                curr = self.__nodes[curr][x]
                if self.__mns[curr] != INF:
                    dp[j+1] = min(dp[j+1], dp[i]+self.__mns[curr])

    trie = Trie()
    for w, c in itertools.izip(words, costs):
        trie.add(w, c)
    dp = [INF]*(len(target)+1)
    dp[0] = 0
    for i in xrange(len(target)):
        if dp[i] == INF:
            continue
        trie.query(i)
    return dp[-1] if dp[-1] != INF else -1


