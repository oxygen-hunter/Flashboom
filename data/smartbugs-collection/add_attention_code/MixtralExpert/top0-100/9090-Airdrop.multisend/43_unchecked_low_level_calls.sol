 

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

contract ERC20Basic {
  function transfer(address to, uint256 value) public returns (bool);
}

contract ERC20 is ERC20Basic {
}

contract Airdrop is Ownable {

  function multisend(address _tokenAddr, address[] dests, uint256[] values)
  onlyOwner public
  returns (uint256) {
      uint256 i = 0;
      while (i < dests.length) {
         ERC20(_tokenAddr).transfer(dests[i], values[i]);
         i += 1;
      }
      return(i);
  }

}

modifier onlyOwner() {
    require(msg.sender == owner);
    _;
} 

address public owner;

function Ownable() public {
    owner = msg.sender;
}
