 

pragma solidity ^0.4.24;

contract Proxy {

  address owner;


    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

  constructor() public {
    owner = msg.sender;
  }

  function forward(address callee, bytes _data) public {
     
    require(callee.delegatecall(_data));  
  }

}
