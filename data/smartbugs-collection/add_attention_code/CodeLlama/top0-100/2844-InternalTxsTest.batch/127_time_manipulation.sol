 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   

    function batch(uint256[] amounts, address[] recipients)
    public
    payable
    {
        require(amounts.length == recipients.length);

        for (uint8 i = 0; i < amounts.length; i++) {
            recipients[i].transfer(amounts[i]);
        }
    }

  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
