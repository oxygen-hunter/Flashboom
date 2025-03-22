 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;



    function add(uint a, uint b) internal pure returns (uint c) {

        c = a + b;

        require(c >= a);

    }


    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
