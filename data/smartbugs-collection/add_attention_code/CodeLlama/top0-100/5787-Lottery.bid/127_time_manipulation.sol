 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   
  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}

event Bid(address sender);

function bid() public
{
    emit Bid(msg.sender);
}
