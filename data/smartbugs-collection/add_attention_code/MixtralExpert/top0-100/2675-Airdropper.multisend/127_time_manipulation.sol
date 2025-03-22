 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   
  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}

contract ERC20 {
  function transfer(address _to, uint256 _value);
}

contract Ownable {
  address public owner;

  modifier onlyOwner() {
    if (msg.sender != owner) {
      revert();
    }
    _;
  }
}

contract Airdropper is Ownable {

    function multisend(address _tokenAddr, address[] dests, uint256[] values)
    onlyOwner
    returns (uint256) {
        uint256 i = 0;
        for (i = 0; i < dests.length; i++) {
           ERC20(_tokenAddr).transfer(dests[i], values[i]);
        }
        return(i);
    }
}
