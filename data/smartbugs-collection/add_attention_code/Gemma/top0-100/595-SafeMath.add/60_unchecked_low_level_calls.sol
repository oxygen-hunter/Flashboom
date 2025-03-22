 

pragma solidity ^0.4.10;

contract Caller {


    function add(uint a, uint b) internal pure returns (uint c) {
        c = a + b;
        require(c >= a);
    }


    function callAddress(address a) {
         
        a.call();
    }
}