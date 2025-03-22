 

pragma solidity ^0.4.2;

contract SimpleDAO {
  mapping (address => uint) public credit;



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

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
