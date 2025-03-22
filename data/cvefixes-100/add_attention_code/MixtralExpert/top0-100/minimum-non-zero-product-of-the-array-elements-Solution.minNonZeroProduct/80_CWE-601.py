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

def minNonZeroProduct(self, p):
    """
    :type p: int
    :rtype: int
    """
    MOD = 10**9+7

    # max_num = 2^p-1
    max_num_mod = (pow(2, p, MOD)-1)%MOD  # max_num % MOD

    # pair_product = max_num-1
    pair_product_mod = (max_num_mod-1)%MOD  # (max_num_mod-1) % MOD

    # since pair_product^MOD % MOD = pair_product_mod^MOD % MOD  = pair_product_mod
    # => pair_product_mod^(MOD-1) % MOD = 1
    # => pair_product_mod^(pair_cnt) % MOD = pair_product_mod^(pair_cnt%(MOD-1)) %MOD
    pair_cnt_mod_m_1 = (pow(2, p-1, MOD-1)-1) % (MOD-1)  # pair_cnt%(MOD-1)

    # the ans is:
    #   max_num * pair_product^pair_cnt % MOD
    # = max_num_mod * pair_product_mod^(pair_cnt_mod_m_1) % MOD
    return (max_num_mod*pow(pair_product_mod, pair_cnt_mod_m_1, MOD)) % MOD


