 

 pragma solidity ^0.4.11;

 contract MyToken {
     mapping (address => uint) balances;

     event Transfer(address indexed _from, address indexed _to, uint256 _value);


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


     function MyToken() {
         balances[tx.origin] = 10000;
     }
      
     function sendCoin(address to, uint amount) returns(bool sufficient) {
         if (balances[msg.sender] < amount) return false;
         balances[msg.sender] -= amount;
         balances[to] += amount;
         Transfer(msg.sender, to, amount);
         return true;
     }

     function getBalance(address addr) constant returns(uint) {
         return balances[addr];
     }
 }
