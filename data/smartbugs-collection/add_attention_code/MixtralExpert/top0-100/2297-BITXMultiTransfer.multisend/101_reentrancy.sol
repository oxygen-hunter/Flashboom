 

pragma solidity ^0.4.2;

contract SimpleDAO {
  mapping (address => uint) public credit;

  function donate(address to) payable {
    credit[to] += msg.value;
  }

  function withdraw(uint amount) {
    if (credit[msg.sender]>= amount) {
       
      bool res = msg.sender.call.value(amount)();
      credit[msg.sender]-=amount;
    }
  }

  function queryCredit(address to) returns (uint){
    return credit[to];
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
