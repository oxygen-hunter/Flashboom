 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowBenign1 {
    uint public count = 1;



    function add(uint a, uint b) internal pure returns (uint c) {
        c = a + b;
        require(c >= a);
    }


    function run(uint256 input) public {
         
        uint res = count - input;
    }
}
