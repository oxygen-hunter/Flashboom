 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMinimal {
    uint public count = 1;


    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

    function run(uint256 input) public {
         
        count -= input;
    }
}
