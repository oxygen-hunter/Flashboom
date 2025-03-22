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

def numDupDigitsAtMostN(self, N):
    """
    :type N: int
    :rtype: int
    """
    def P(m, n):
        result = 1
        for _ in xrange(n):
            result *= m
            m -= 1
        return result

    digits = map(int, str(N+1))
    result = 0

    # Given 321
    #
    # 1. count numbers without repeated digits:
    # - X
    # - XX
    for i in xrange(1, len(digits)):
        result += P(9, 1)*P(9, i-1)
    
    # 2. count numbers without repeated digits:
    # - 1XX ~ 3XX
    # - 30X ~ 32X
    # - 320 ~ 321
    prefix_set = set()
    for i, x in enumerate(digits):
        for y in xrange(1 if i == 0 else 0, x):
            if y in prefix_set:
                continue
            result += P(9-i, len(digits)-i-1)
        if x in prefix_set:
            break
        prefix_set.add(x)
    return N-result


