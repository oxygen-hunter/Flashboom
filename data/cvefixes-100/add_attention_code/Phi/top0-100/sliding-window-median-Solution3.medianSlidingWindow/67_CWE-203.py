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

def medianSlidingWindow(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: List[float]
    """
    def lazy_delete(heap, to_remove, sign):
        while heap and sign*heap[0] in to_remove:
            to_remove[sign*heap[0]] -= 1
            if not to_remove[sign*heap[0]]:
                del to_remove[sign*heap[0]]
            heapq.heappop(heap)

    min_heap, max_heap = [], []
    for i in xrange(k):
        if i%2 == 0:
            heapq.heappush(min_heap, -heapq.heappushpop(max_heap, -nums[i]))
        else:
            heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
    result = [float(min_heap[0])] if k%2 else [(min_heap[0]-max_heap[0])/2.0]
    to_remove = collections.defaultdict(int)
    for i in xrange(k, len(nums)):
        heapq.heappush(max_heap, -heapq.heappushpop(min_heap, nums[i]))
        if nums[i-k] > -max_heap[0]:
            heapq.heappush(min_heap, -heapq.heappop(max_heap))
        to_remove[nums[i-k]] += 1
        lazy_delete(max_heap, to_remove, -1)
        lazy_delete(min_heap, to_remove, 1)
        result.append(float(min_heap[0]) if k%2 else (min_heap[0]-max_heap[0])/2.0)
    return result


