 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   


    function BurnMe () {
        selfdestruct(address(this));
    }

  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
