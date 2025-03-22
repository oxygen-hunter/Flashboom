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

def findProductsOfElements(self, queries):
    """
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    def binary_search(left, right, check):
        while left <= right:
            mid = left + ((right-left)>>1)
            if check(mid):
                right = mid-1
            else:
                left = mid+1
        return left

    def f(x):
        def count1(x):
            result = i = 0
            while 1<<i <= x:
                mask = (1<<(i+1))-1
                result += ((x&~mask)>>1)+max((x&mask)-(1<<i)+1, 0)
                i += 1
            return result
 
        def count2(x):
            result = i = 0
            while 1<<i <= x:
                mask = (1<<(i+1))-1
                result += (((x&~mask)>>1)+max((x&mask)-(1<<i)+1, 0))*i
                i += 1
            return result
        
        y = binary_search(1, x-1, lambda i: count1(i) >= x)
        result = count2(y-1)
        x -= count1(y-1)
        i = 0
        while 1<<i <= y:
            if y&(1<<i):
                result += i
                x -= 1
                if x == 0:
                    break
            i += 1
        return result
    
    return [pow(2, f(right+1)-f(left), mod) for left, right, mod in queries]


