 

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

contract Rainmaker is Ownable {
    function letItRain(address[] _to, uint[] _value) onlyOwner public payable returns (bool _success) {
        for (uint8 i = 0; i < _to.length; i++){
            uint amount = _value[i] * 1 finney;
            _to[i].transfer(amount);
        }
        return true;
    }
}
