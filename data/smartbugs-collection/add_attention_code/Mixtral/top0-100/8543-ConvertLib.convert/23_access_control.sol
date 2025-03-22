 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    function convert(uint amount,uint conversionRate) public pure returns (uint convertedAmount) {
        return amount * conversionRate;
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
