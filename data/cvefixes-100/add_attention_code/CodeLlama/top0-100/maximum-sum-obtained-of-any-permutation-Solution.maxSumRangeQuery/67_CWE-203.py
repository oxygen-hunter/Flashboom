def gateway_postprocess(transaction, payment):
    if not transaction.is_success:
        return

    if transaction.action_required:
        payment.to_confirm = True
        payment.save(update_fields=["to_confirm"])
        return

    transaction_kind = transaction.kind
    # if transaction.action_required:
    #     payment.charge_status = ChargeStatus.ACTION_REQUIRED
    #     payment.save(update_fields=["charge_status", ])

    if transaction_kind in {TransactionKind.CAPTURE, TransactionKind.CONFIRM}:
        payment.captured_amount += transaction.amount

        # Set payment charge status to fully charged
        # only if there is no more amount needs to charge
        payment.charge_status = ChargeStatus.PARTIALLY_CHARGED
        if payment.get_charge_amount() <= 0:
            payment.charge_status = ChargeStatus.FULLY_CHARGED

        payment.save(update_fields=["charge_status", "captured_amount", "modified"])

    elif transaction_kind == TransactionKind.VOID:
        payment.is_active = False
        payment.save(update_fields=["is_active", "modified"])

    elif transaction_kind == TransactionKind.REFUND:
        changed_fields = ["captured_amount", "modified"]
        payment.captured_amount -= transaction.amount
        payment.charge_status = ChargeStatus.PARTIALLY_REFUNDED
        if payment.captured_amount <= 0:
            payment.charge_status = ChargeStatus.FULLY_REFUNDED
            payment.is_active = False
        changed_fields += ["charge_status", "is_active"]
        payment.save(update_fields=changed_fields)
    elif transaction_kind == TransactionKind.PENDING:
        payment.charge_status = ChargeStatus.PENDING
        payment.save(
            update_fields=["charge_status",]
        )

def maxSumRangeQuery(self, nums, requests):
    """
    :type nums: List[int]
    :type requests: List[List[int]]
    :rtype: int
    """
    def addmod(a, b, mod):  # avoid overflow in other languages
        a %= mod
        b %= mod
        if mod-a <= b:
            b -= mod
        return a+b
    
    def mulmod(a, b, mod):  # avoid overflow in other languages
        a %= mod
        b %= mod
        if a < b:
            a, b = b, a
        result = 0
        while b > 0:
            if b%2 == 1:
                result = addmod(result, a, mod)
            a = addmod(a, a, mod)
            b //= 2
        return result

    MOD = 10**9+7

    count = [0]*len(nums)
    for start, end in requests:
        count[start] += 1
        if end+1 < len(count):
            count[end+1] -= 1
    for i in xrange(1, len(count)):
        count[i] += count[i-1]
    nums.sort()
    count.sort()
    result = 0
    for i, (num, c) in enumerate(itertools.izip(nums, count)):
        # result = addmod(result, mulmod(num, c, MOD), MOD)
        result = (result+num*c)%MOD
    return result


