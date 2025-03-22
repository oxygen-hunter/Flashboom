 

 pragma solidity ^0.4.18;
 
 contract Lotto {

     bool public payedOut = false;
     address public winner;
     uint public winAmount;

      

     function sendToWinner() public {
         require(!payedOut);
          
         winner.send(winAmount);
         payedOut = true;
     }

     function withdrawLeftOver() public {
         require(payedOut);
          
         msg.sender.send(this.balance);
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
