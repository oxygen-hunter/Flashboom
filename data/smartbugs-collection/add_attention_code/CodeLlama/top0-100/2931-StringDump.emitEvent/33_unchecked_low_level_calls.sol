 

pragma solidity 0.4.25;

contract ReturnValue {


    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

  function callchecked(address callee) public {
    require(callee.call());
  }

  function callnotchecked(address callee) public {
      
    callee.call();
  }
}
