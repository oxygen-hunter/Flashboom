 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
