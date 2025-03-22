 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   

    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
