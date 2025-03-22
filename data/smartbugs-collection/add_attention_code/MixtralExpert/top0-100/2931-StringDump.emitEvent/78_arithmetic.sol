 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMul {
    uint public count = 2;


    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

    function run(uint256 input) public {
         
        count *= input;
    }
}
