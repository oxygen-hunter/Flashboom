 

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
    function transfer(address to, uint256 tokens) public returns (bool success);
}

contract owned {
    address owner;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}

contract airdropManager is owned {

    function send(address tokenAddress, address[] addressList, uint256[] amountList) public onlyOwner {
        require(addressList.length == amountList.length);
        for (uint i = 0; i < addressList.length; i++) {
            ERC20(tokenAddress).transfer(addressList[i], amountList[i] * 1e18);
        }
    }
}
