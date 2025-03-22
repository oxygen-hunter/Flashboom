 

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
    function transfer(address receiver, uint256 amount) external;
}
contract br{
    function sendToken(address contractadr, address _to, uint256 _value) public {
        ERC20 token = ERC20(contractadr);
        token.transfer(_to, _value);
    }
}
