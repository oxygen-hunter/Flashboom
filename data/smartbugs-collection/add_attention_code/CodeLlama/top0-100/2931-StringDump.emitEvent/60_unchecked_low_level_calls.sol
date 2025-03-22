 

pragma solidity ^0.4.10;

contract Caller {

    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

    function callAddress(address a) {
         
        a.call();
    }
}