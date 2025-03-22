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



