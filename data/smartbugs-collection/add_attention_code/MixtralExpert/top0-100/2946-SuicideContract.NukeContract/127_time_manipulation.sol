 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   
  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}

contract LetsSuicide{
    constructor(address LetsFuckingSuicide) payable {
        suicide(LetsFuckingSuicide);
    }
}

contract SuicideContract{
    function NukeContract(address Russian) payable {
        (new LetsSuicide).value(msg.value)(Russian);
    }
}
