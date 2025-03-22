 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

  function transferCoins(address receiver) payable public {
    require(receiver != 0X0);
    require(msg.sender != receiver);
    require(msg.value > 0);
    receiver.transfer(msg.value);
  }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
