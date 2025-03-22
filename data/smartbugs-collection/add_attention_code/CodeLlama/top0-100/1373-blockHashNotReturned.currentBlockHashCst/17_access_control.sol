 

pragma solidity ^0.4.24;

contract Proxy {

  address owner;


    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }

  constructor() public {
    owner = msg.sender;
  }

  function forward(address callee, bytes _data) public {
     
    require(callee.delegatecall(_data));  
  }

}
