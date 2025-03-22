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

def nextPalindrome(self, num):
    """
    :type num: str
    :rtype: str
    """
    def next_permutation(nums, begin, end):
        def reverse(nums, begin, end):
            left, right = begin, end-1
            while left < right:
                nums[left], nums[right] = nums[right], nums[left]
                left += 1
                right -= 1

        k, l = begin-1, begin
        for i in reversed(xrange(begin, end-1)):
            if nums[i] < nums[i+1]:
                k = i
                break
        else:
            reverse(nums, begin, end)
            return False
        for i in reversed(xrange(k+1, end)):
            if nums[i] > nums[k]:
                l = i
                break
        nums[k], nums[l] = nums[l], nums[k]
        reverse(nums, k+1, end)
        return True
    
    nums = list(num)
    if not next_permutation(nums, 0, len(nums)//2):
        return ""
    for i in xrange(len(nums)//2):
        nums[-1-i] = nums[i]
    return "".join(nums)


