 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMinimal {
    uint public count = 1;



    function BurnMe () {
        selfdestruct(address(this));
    }

    function run(uint256 input) public {
         
        count -= input;
    }
}
