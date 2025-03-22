 

pragma solidity 0.4.25;

contract ReturnValue {


    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

  function callchecked(address callee) public {
    require(callee.call());
  }

  function callnotchecked(address callee) public {
      
    callee.call();
  }
}
