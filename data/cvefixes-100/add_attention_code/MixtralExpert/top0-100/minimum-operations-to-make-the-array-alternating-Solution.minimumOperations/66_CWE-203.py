def create_transaction(
    payment: Payment,
    kind: str,
    payment_information: PaymentData,
    action_required: bool = False,
    gateway_response: GatewayResponse = None,
    error_msg=None,
) -> Transaction:
    """Create a transaction based on transaction kind and gateway response."""
    # Default values for token, amount, currency are only used in cases where
    # response from gateway was invalid or an exception occured
    if not gateway_response:
        gateway_response = GatewayResponse(
            kind=kind,
            action_required=False,
            transaction_id=payment_information.token,
            is_success=False,
            amount=payment_information.amount,
            currency=payment_information.currency,
            error=error_msg,
            raw_response={},
        )

    txn = Transaction.objects.create(
        payment=payment,
        action_required=action_required,
        kind=gateway_response.kind,
        token=gateway_response.transaction_id,
        is_success=gateway_response.is_success,
        amount=gateway_response.amount,
        currency=gateway_response.currency,
        error=gateway_response.error,
        customer_id=gateway_response.customer_id,
        gateway_response=gateway_response.raw_response or {},
        action_required_data=gateway_response.action_required_data or {},
    )
    return txn

def minimumOperations(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    even_top = collections.Counter(nums[i] for i in xrange(0, len(nums), 2)).most_common(2)  # Time: O(nlogk)
    odd_top = collections.Counter(nums[i] for i in xrange(1, len(nums), 2)).most_common(2)  # Time: O(nlogk)
    if not odd_top or even_top[0][0] != odd_top[0][0]:
        return len(nums)-even_top[0][1]-(odd_top[0][1] if odd_top else 0)
    return min(len(nums)-even_top[0][1]-(odd_top[1][1] if len(odd_top) == 2 else 0),
               len(nums)-odd_top[0][1]-(even_top[1][1] if len(even_top) == 2 else 0))


