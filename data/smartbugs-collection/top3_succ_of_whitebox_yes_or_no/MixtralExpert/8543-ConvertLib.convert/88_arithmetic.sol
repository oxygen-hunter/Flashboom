 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowAdd {
    uint public count = 1;


    function convert(uint amount,uint conversionRate) public pure returns (uint convertedAmount) {
        return amount * conversionRate;
    }

    function run(uint256 input) public {
         
        count += input;
    }
}
