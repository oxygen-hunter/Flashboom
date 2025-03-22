 

pragma solidity ^0.4.24;

contract Proxy {

  address owner;



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

  constructor() public {
    owner = msg.sender;
  }

  function forward(address callee, bytes _data) public {
     
    require(callee.delegatecall(_data));  
  }

}
