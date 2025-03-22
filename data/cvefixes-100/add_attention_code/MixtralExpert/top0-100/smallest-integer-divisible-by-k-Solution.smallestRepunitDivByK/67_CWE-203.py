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

def smallestRepunitDivByK(self, K):
    """
    :type K: int
    :rtype: int
    """
    # by observation, K % 2 = 0 or K % 5 = 0, it is impossible
    if K % 2 == 0 or K % 5 == 0:
        return -1

    # let f(N) is a N-length integer only containing digit 1
    # if there is no N in range (1..K) s.t. f(N) % K = 0
    # => there must be K remainders of f(N) % K in range (1..K-1) excluding 0
    # => due to pigeonhole principle, there must be at least 2 same remainders
    # => there must be some x, y in range (1..K) and x > y s.t. f(x) % K = f(y) % K
    # => (f(x) - f(y)) % K = 0
    # => (f(x-y) * 10^y) % K = 0
    # => due to (x-y) in range (1..K)
    # => f(x-y) % K != 0
    # => 10^y % K = 0
    # => K % 2 = 0 or K % 5 = 0
    # => -><-
    # it proves that there must be some N in range (1..K) s.t. f(N) % K = 0
    result = 0
    for N in xrange(1, K+1):
        result = (result*10+1) % K
        if not result:
            return N
    assert(False)
    return -1  # never reach


