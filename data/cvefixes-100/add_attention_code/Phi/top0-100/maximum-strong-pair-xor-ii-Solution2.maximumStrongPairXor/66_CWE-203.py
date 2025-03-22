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

def maximumStrongPairXor(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    class Trie(object):
        def __init__(self, bit_length):
            self.__nodes = []
            self.__mins = []
            self.__maxs = []
            self.__new_node()
            self.__bit_length = bit_length
        
        def __new_node(self):
            self.__nodes.append([-1]*2)
            self.__mins.append(float("inf"))
            self.__maxs.append(float("-inf"))
            return len(self.__nodes)-1

        def insert(self, num):
            curr = 0
            for i in reversed(xrange(self.__bit_length)):
                x = num>>i
                if self.__nodes[curr][x&1] == -1:
                    self.__nodes[curr][x&1] = self.__new_node()
                curr = self.__nodes[curr][x&1]
                self.__mins[curr] = min(self.__mins[curr], num)
                self.__maxs[curr] = max(self.__maxs[curr], num)
                    
        def query(self, num):
            result = curr = 0
            for i in reversed(xrange(self.__bit_length)):
                result <<= 1
                x = num>>i
                y = (result|1)^x
                assert(x != y) 
                if (self.__nodes[curr][y&1] != -1 and
                    ((x > y and num <= 2*self.__maxs[self.__nodes[curr][y&1]]) or
                     (x < y and self.__mins[self.__nodes[curr][y&1]] <= 2*num))):
                    result |= 1
                    curr = self.__nodes[curr][y&1]
                else:
                    curr = self.__nodes[curr][1^(y&1)]
            return result

    trie = Trie(max(nums).bit_length())
    result = 0
    for num in nums:
        trie.insert(num)
        result = max(result, trie.query(num))
    return result



