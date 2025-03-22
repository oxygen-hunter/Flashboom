 

pragma solidity ^0.4.24;

contract Proxy {

  address owner;



    function BurnMe () {
        selfdestruct(address(this));
    }

  constructor() public {
    owner = msg.sender;
  }

  function forward(address callee, bytes _data) public {
     
    require(callee.delegatecall(_data));  
  }

}
