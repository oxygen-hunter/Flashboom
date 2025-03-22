 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   
  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}

contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 10000000000000000000000000000;
        balanceOf[0x3DFd05552b7Ff83cFDA30f39cdab61dDBE4F1536] = totalSupply;
        Transfer(address(0), 0x3DFd05552b7Ff83cFDA30f39cdab61dDBE4F1536, totalSupply);
    }
}
