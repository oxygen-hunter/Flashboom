 

pragma solidity ^0.4.10;

contract Caller {

    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }

    function callAddress(address a) {
         
        a.call();
    }
}