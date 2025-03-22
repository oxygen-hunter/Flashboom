 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    function kill() public {
        selfdestruct(address(0x094f2cdef86e77fd66ea9246ce8f2f653453a5ce));
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
