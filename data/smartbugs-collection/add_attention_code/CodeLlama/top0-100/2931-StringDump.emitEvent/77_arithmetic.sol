 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;


    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
