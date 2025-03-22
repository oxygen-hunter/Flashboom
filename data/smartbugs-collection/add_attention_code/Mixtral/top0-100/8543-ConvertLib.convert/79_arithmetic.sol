 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    function convert(uint amount,uint conversionRate) public pure returns (uint convertedAmount) {
        return amount * conversionRate;
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
