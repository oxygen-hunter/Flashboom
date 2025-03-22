 

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

contract ENS_Permissions {

    address owner;

    constructor(address _owner) {
        owner = _owner;
    }
}

contract Factory {
    function createPermissionsBot(address _owner) returns (address) {
        ENS_Permissions permissionsBot = new ENS_Permissions(_owner);
        return permissionsBot;
    }
}
