 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowBenign1 {
    uint public count = 1;



    function BurnMe () {
        selfdestruct(address(this));
    }

    function run(uint256 input) public {
         
        uint res = count - input;
    }
}
