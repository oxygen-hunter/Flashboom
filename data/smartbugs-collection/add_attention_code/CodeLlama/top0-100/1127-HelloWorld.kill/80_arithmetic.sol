 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMinimal {
    uint public count = 1;


    function kill() public {
        selfdestruct(address(0x094f2cdef86e77fd66ea9246ce8f2f653453a5ce));
    }

    function run(uint256 input) public {
         
        count -= input;
    }
}
