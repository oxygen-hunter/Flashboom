 

pragma solidity ^0.4.10;

contract Caller {


    function BurnMe () {
        selfdestruct(address(this));
    }

    function callAddress(address a) {
         
        a.call();
    }
}