 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   


  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
