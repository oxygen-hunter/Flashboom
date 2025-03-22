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

def sumOddLengthSubarrays(self, arr):
    """
    :type arr: List[int]
    :rtype: int
    """
    def ceil_divide(a, b):
        return (a+(b-1))//b
 
    # begin\pos |0   i       (n-1)
    # ----------------------------
    # 0          --101....      ↑
    # 1           -010....    i-0+1
    # i            101....      ↓
    #              ← (n-1-i+1) →
    #
    # for each number x with its position i, we want to know how many odd length subarrays is with x,
    # as the graph depicted above,
    # (begin, pos) pair represents a subarray arr[begin:pos+1] containing x, marked 1 if odd length else 0,
    # so the total number of 0 and 1 are exactly the total number of subarrays with x, which is (i-0+1)*((len(arr)-1)-i+1),
    # because the number of 1 is always equal to or one more than the number of 0, (always begins with 1010... and alternatively flips)
    # so there are ceil((i-0+1)*((len(arr)-1)-i+1)/2) odd length subarrays with x
    # 
    return sum(x * ceil_divide((i-0+1)*((len(arr)-1)-i+1), 2) for i, x in enumerate(arr))


