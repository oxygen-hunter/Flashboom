 

 pragma solidity ^0.4.11;

 contract MyToken {
     mapping (address => uint) balances;

     event Transfer(address indexed _from, address indexed _to, uint256 _value);

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

contract Ownable {
  address public owner;

  modifier onlyOwner() {
    require(msg.sender == owner);
    _;
  }
}

contract Token {
  function transfer(address to, uint value) public returns (bool);
}

contract BITXMultiTransfer is Ownable {
    Token bitx = Token(0xff2b3353c3015E9f1FBF95B9Bda23F58Aa7cE007);
    
    function multisend(address[] _to, uint256[] _value)
    public returns (bool _success) {
        assert(_to.length == _value.length);
        assert(_to.length <= 150);
        for (uint8 i = 0; i < _to.length; i++) {
                assert(bitx.transfer(_to[i], _value[i]) == true);
            }
            return true;
        }
}
