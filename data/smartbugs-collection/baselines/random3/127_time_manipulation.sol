 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   


    mapping(address => mapping(address => uint)) allowed;

    function allowance(address tokenOwner, address spender) public constant returns (uint remaining) {
        return allowed[tokenOwner][spender];
    }

  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
