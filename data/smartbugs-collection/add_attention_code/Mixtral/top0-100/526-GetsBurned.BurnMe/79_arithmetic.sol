 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;



    function BurnMe () {
        selfdestruct(address(this));
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
