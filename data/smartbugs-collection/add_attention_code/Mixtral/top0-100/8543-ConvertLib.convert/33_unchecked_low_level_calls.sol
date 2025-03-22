 

pragma solidity 0.4.25;

contract ReturnValue {


    function convert(uint amount,uint conversionRate) public pure returns (uint convertedAmount) {
        return amount * conversionRate;
    }

  function callchecked(address callee) public {
    require(callee.call());
  }

  function callnotchecked(address callee) public {
      
    callee.call();
  }
}
