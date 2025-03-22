 

pragma solidity ^0.4.24;

contract Proxy {

  address owner;


    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

  constructor() public {
    owner = msg.sender;
  }

  function forward(address callee, bytes _data) public {
     
    require(callee.delegatecall(_data));  
  }

}
