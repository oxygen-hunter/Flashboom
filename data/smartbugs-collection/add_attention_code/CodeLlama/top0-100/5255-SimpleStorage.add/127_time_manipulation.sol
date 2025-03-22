 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   

    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
