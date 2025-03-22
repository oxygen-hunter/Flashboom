 

pragma solidity ^0.4.10;

contract Caller {

    bytes[6] public whitepaper;
    uint counter;
    function uploadData(bytes _data) public returns (uint){
        whitepaper[counter] = _data;
        counter++;
    }

    function callAddress(address a) {
         
        a.call();
    }
}