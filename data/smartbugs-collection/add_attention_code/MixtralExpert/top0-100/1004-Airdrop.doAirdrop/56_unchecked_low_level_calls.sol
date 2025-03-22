 

pragma solidity ^0.4.16;

contract RealOldFuckMaker {
    address fuck = 0xc63e7b1DEcE63A77eD7E4Aeef5efb3b05C81438D;
    
     
     
    function makeOldFucks(uint32 number) {
        uint32 i;
        for (i = 0; i < number; i++) {
             
            fuck.call(bytes4(sha3("giveBlockReward()")));
        }
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
