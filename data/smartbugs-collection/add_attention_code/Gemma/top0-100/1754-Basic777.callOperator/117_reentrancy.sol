 

pragma solidity ^0.4.24;

contract Reentrancy_cross_function {

     
    mapping (address => uint) private userBalances;


  function callOperator(
    address _operator,
    address _from,
    address _to,
    uint256 _value,
    bytes _userData,
    bytes _operatorData,
    bool _preventLocking
  ) private {
    address recipientImplementation = interfaceAddr(_to, "ERC777TokensOperator");
    if (recipientImplementation != 0) {
      ERC777TokensOperator(recipientImplementation).madeOperatorForTokens(
        _operator, 
        _from, 
        _to, 
        _value, 
        _userData, 
        _operatorData
      );
    } else if (_preventLocking) {
      require(
        isRegularAddress(_to),
        "When '_preventLocking' is true, you cannot invoke 'callOperator' to a contract address that does not support the 'ERC777TokensOperator' interface"
      );
    }
  }


    function transfer(address to, uint amount) {
        if (userBalances[msg.sender] >= amount) {
            userBalances[to] += amount;
            userBalances[msg.sender] -= amount;
        }
    }

    function withdrawBalance() public {
        uint amountToWithdraw = userBalances[msg.sender];
         
        (bool success, ) = msg.sender.call.value(amountToWithdraw)("");  
        require(success);
        userBalances[msg.sender] = 0;
    }
}
