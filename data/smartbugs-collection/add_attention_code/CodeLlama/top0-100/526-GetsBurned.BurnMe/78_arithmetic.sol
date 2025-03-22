 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMul {
    uint public count = 2;



    function BurnMe () {
        selfdestruct(address(this));
    }

    function run(uint256 input) public {
         
        count *= input;
    }
}
