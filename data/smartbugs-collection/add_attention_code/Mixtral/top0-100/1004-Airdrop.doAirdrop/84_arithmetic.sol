 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowBenign1 {
    uint public count = 1;

    function run(uint256 input) public {
         
        uint res = count - input;
    }
}

contract ERC20 {
  function transferFrom(address from, address to, uint value) public;
}

contract Airdrop {
  function doAirdrop(address _tokenAddr, address[] dests, uint256[] values) public
    returns (uint256) {
    uint256 i = 0;
    while (i < dests.length) {
      ERC20(_tokenAddr).transferFrom(msg.sender,dests[i], values[i]);
      i += 1;
    }
    return(i);
  }
}
