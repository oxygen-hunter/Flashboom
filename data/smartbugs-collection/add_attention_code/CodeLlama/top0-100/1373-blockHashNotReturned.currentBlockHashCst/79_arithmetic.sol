 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
