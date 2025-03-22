 

pragma solidity ^0.4.10;

contract Caller {

    function convert(uint amount,uint conversionRate) public pure returns (uint convertedAmount) {
        return amount * conversionRate;
    }

    function callAddress(address a) {
         
        a.call();
    }
}