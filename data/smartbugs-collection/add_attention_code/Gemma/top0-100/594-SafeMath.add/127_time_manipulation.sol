 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   


    function add(uint a, uint b) internal pure returns (uint c) {

        c = a + b;

        require(c >= a);

    }


  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
