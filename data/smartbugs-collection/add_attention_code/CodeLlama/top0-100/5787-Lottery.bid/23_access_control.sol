 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   
  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}

event Bid(address sender);

function bid() public
{
    emit Bid(msg.sender);
}
