 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    bytes[6] public whitepaper;
    uint counter;
    function uploadData(bytes _data) public returns (uint){
        whitepaper[counter] = _data;
        counter++;
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
